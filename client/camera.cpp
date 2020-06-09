#include <iostream>
#include "camera.h"
#include "visual_config.h"
#include "decoration.h"

Camera::Camera(const VisualComponent &follow_component,int map_size, int tile_size)
    : follow_component(follow_component),
      x_center_tile(follow_component.get_x()),
      y_center_tile(follow_component.get_y()),
      map_size(map_size),
      tile_size(tile_size),
      width_tiles(15),
      height_tiles(10),
      _is_locked_x(false),
      _is_locked_y(false) {}

Camera::~Camera(){};

bool Camera::_is_within_visual_range(VisualComponent* component) {
    /* return (
        (component->get_x() - 2< x_center_tile + (width_tiles / 2)) &&
        (component->get_x() + 2 > x_center_tile - (width_tiles / 2)) &&
        (component->get_y() + 2 > y_center_tile - (height_tiles / 2)) &&
        (component->get_y() - 2 < y_center_tile + (height_tiles / 2))); */
    return true;
}

SDLArea Camera::_get_render_area(VisualComponent* component) {
    int camera_corner_x_tile = x_center_tile - (width_tiles / 2);
    int camera_corner_y_tile = y_center_tile - (height_tiles / 2);

    int relative_x_tile = component->get_x() - camera_corner_x_tile;
    int relative_y_tile = component->get_y() - camera_corner_y_tile;

    int camera_offset_x =
        (follow_component.get_x_offset() * tile_size) / OFFSET_GRANULARITY;
    int camera_offset_y =
        (follow_component.get_y_offset() * tile_size) / OFFSET_GRANULARITY;

    if (_is_locked_x) camera_offset_x = 0;
    if (_is_locked_y) camera_offset_y = 0;
    int x_render_base =
        (relative_x_tile * tile_size) +
        (component->get_x_offset() * tile_size) / OFFSET_GRANULARITY;
    
    int y_render_base =
        (relative_y_tile * tile_size) +
        (component->get_y_offset() * tile_size) / OFFSET_GRANULARITY;

    /* En las coordenadas donde esta el componente, se renderiza el tile
    de abajo a la izquierda de la textura. */
    y_render_base -=
        ((component->get_height() * tile_size) / SIZE_GRANULARITY) - tile_size;

    return SDLArea(x_render_base - camera_offset_x,
                   y_render_base - camera_offset_y,
                   (component->get_width() * tile_size) / SIZE_GRANULARITY,
                   (component->get_height() * tile_size) / SIZE_GRANULARITY);
}

void Camera::_update_position() {
    if(follow_component.get_x() <= map_size - (width_tiles / 2) && follow_component.get_x() >= (width_tiles/2)){
        x_center_tile = follow_component.get_x();
        if(!follow_component.is_transitioning()) _is_locked_x = false;
    }else{
        _is_locked_x = true;
    }

    if(follow_component.get_y() <= map_size - (height_tiles / 2) && follow_component.get_y() >= (height_tiles/2)){
        y_center_tile = follow_component.get_y();
        if(!follow_component.is_transitioning()) _is_locked_y = false;
    }else{
        _is_locked_y = true;
    }
 
}

void Camera::render_components(std::vector<VisualComponent*> components) {
    _update_position();
    for (auto component = components.begin(); component != components.end();
         ++component) {
        if (!_is_within_visual_range(*component)) continue;
        SDLArea dest = _get_render_area(*component);
        (*component)->render(dest);
    }
    /* Actualiza el estado visual de todos los componentes luego de renderizar.*/
    for (auto component = components.begin(); component != components.end();
         ++component) {
        (*component)->update();
    }
}


void Camera::render_map_layer(std::vector<Decoration> &layer){
    _update_position();
    for(auto tile = layer.begin(); tile != layer.end(); ++tile){
        SDLArea dest = _get_render_area(&(*tile));
        (*tile).render(dest);
    }
}