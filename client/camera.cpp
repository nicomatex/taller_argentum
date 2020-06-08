#include "camera.h"

#include <iostream>

#include "visual_config.h"

#define TILE_SIZE 64
#define MAP_SIZE 25

Camera::Camera(const VisualComponent& follow_component)
    : follow_component(follow_component),
      x_center_tile(follow_component.get_x()),
      y_center_tile(follow_component.get_y()),
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
        (follow_component.get_x_offset() * TILE_SIZE) / OFFSET_GRANULARITY;
    int camera_offset_y =
        (follow_component.get_y_offset() * TILE_SIZE) / OFFSET_GRANULARITY;

    if (_is_locked_x) camera_offset_x = 0;
    if (_is_locked_y) camera_offset_y = 0;

    int x_render_base =
        (relative_x_tile * TILE_SIZE) +
        (component->get_x_offset() * TILE_SIZE) / OFFSET_GRANULARITY;
    int y_render_base =
        (relative_y_tile * TILE_SIZE) +
        (component->get_y_offset() * TILE_SIZE) / OFFSET_GRANULARITY;

    /* En las coordenadas donde esta el componente, se renderiza el tile
    de abajo a la izquierda de la textura. */
    y_render_base -=
        ((component->get_height() * TILE_SIZE) / SIZE_GRANULARITY) - TILE_SIZE;

    return SDLArea(x_render_base - camera_offset_x,
                   y_render_base - camera_offset_y,
                   (component->get_width() * TILE_SIZE) / SIZE_GRANULARITY,
                   (component->get_height() * TILE_SIZE) / SIZE_GRANULARITY);
}

void Camera::_update_position() {
    x_center_tile = follow_component.get_x();
    y_center_tile = follow_component.get_y();

    if (x_center_tile >= MAP_SIZE - (width_tiles / 2)) {
        x_center_tile = MAP_SIZE - (width_tiles / 2);

        /* Para esperar que termine la animacion. */
        if (!follow_component.is_transitioning() == 0) _is_locked_x = true;
    } else if (x_center_tile <= width_tiles / 2) {
        x_center_tile = (width_tiles / 2);

        /* Para esperar que termine la animacion. */
        if (!follow_component.is_transitioning()) _is_locked_x = true;
    } else {
        _is_locked_x = false;
    }

    if (y_center_tile >= MAP_SIZE - (height_tiles / 2)) {
        y_center_tile = MAP_SIZE - (height_tiles / 2);

        /* Para esperar que termine la animacion. */
        if (!follow_component.is_transitioning()) _is_locked_y = true;
    } else if (y_center_tile <= height_tiles / 2) {
        y_center_tile = height_tiles / 2;

        /* Para esperar que termine la animacion. */
        if (!follow_component.is_transitioning()) _is_locked_y = true;
    } else {
        _is_locked_y = false;
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
