#include "camera.h"

#include <cmath>
#include <iostream>

#include "decoration.h"
#include "engine_config.h"

Camera::Camera(const PositionComponent &follow_component, int map_size,
               int tile_size, int viewport_width, int viewport_height,
               int speed)
    : follow_component(follow_component),
      x_center_tile(follow_component.get_x()),
      y_center_tile(follow_component.get_y()),
      map_size(map_size),
      tile_size(tile_size),
      width_tiles(viewport_width),
      height_tiles(viewport_height),
      speed(speed),
      camera_offset_x(0),
      camera_offset_y(0) {}

Camera::~Camera(){};

bool Camera::_is_within_visual_range(RenderizableObject *component) {
    /* return (
        (component->get_x() - 2< x_center_tile + (width_tiles / 2)) &&
        (component->get_x() + 2 > x_center_tile - (width_tiles / 2)) &&
        (component->get_y() + 2 > y_center_tile - (height_tiles / 2)) &&
        (component->get_y() - 2 < y_center_tile + (height_tiles / 2))); */
    return true;
}

SDLArea Camera::_get_render_area(RenderizableObject *component, int x, int y,
                                 int x_tmp_offset, int y_tmp_offset) {
    int camera_corner_x_tile = x_center_tile - (width_tiles / 2);
    int camera_corner_y_tile = y_center_tile - (height_tiles / 2);

    int relative_x_tile = x - camera_corner_x_tile;
    int relative_y_tile = y - camera_corner_y_tile;

    int x_render_base =
        (relative_x_tile * tile_size) +
        ((component->get_x_offset() + x_tmp_offset) * tile_size) /
            OFFSET_GRANULARITY;

    int y_render_base =
        (relative_y_tile * tile_size) +
        ((component->get_y_offset() + y_tmp_offset) * tile_size) /
            OFFSET_GRANULARITY;

    /* En las coordenadas donde esta el componente, se renderiza el tile
    de abajo a la izquierda de la textura. */
    y_render_base -=
        ((component->get_height() * tile_size) / SIZE_GRANULARITY) - tile_size;

    return SDLArea(x_render_base - camera_offset_x,
                   y_render_base - camera_offset_y,
                   (component->get_width() * tile_size) / SIZE_GRANULARITY,
                   (component->get_height() * tile_size) / SIZE_GRANULARITY);
}

SDLArea Camera::_get_render_area(Decoration &decoration) {
    int camera_corner_x_tile = x_center_tile - (width_tiles / 2);
    int camera_corner_y_tile = y_center_tile - (height_tiles / 2);

    int relative_x_tile = decoration.get_x() - camera_corner_x_tile;
    int relative_y_tile = decoration.get_y() - camera_corner_y_tile;

    int x_render_base =
        (relative_x_tile * tile_size) +
        ((decoration.get_x_offset()) * tile_size) / OFFSET_GRANULARITY;

    int y_render_base =
        (relative_y_tile * tile_size) +
        ((decoration.get_y_offset()) * tile_size) / OFFSET_GRANULARITY;

    /* En las coordenadas donde esta el componente, se renderiza el tile
    de abajo a la izquierda de la textura. */
    y_render_base -=
        ((decoration.get_height() * tile_size) / SIZE_GRANULARITY) - tile_size;


    return SDLArea(x_render_base - camera_offset_x,
                   y_render_base - camera_offset_y,
                   (decoration.get_width() * tile_size) / SIZE_GRANULARITY,
                   (decoration.get_height() * tile_size) / SIZE_GRANULARITY);
}

void Camera::_update_offset() {
    int movement_transition_time = 1000 / speed;

    int delta_offset = (tile_size * movement_timer.get_ticks());
    delta_offset /= movement_transition_time;

    bool stop_x = false;
    bool stop_y = false;

    float smooth_factor_x = (float)abs(camera_offset_x) / (float)tile_size;
    float smooth_factor_y = (float)abs(camera_offset_y) / (float)tile_size;

    if(smooth_factor_x < 0.7) smooth_factor_x = 0.7;
    if(smooth_factor_y < 0.7) smooth_factor_y = 0.7;

    if (camera_offset_x > 0) {
        camera_offset_x -= delta_offset * smooth_factor_x;
        if (camera_offset_x <= 0) stop_x = true;
    } else if (camera_offset_x < 0) {
        camera_offset_x += delta_offset * smooth_factor_x;
        if (camera_offset_x >= 0) stop_x = true;
    }

    if (camera_offset_y > 0) {
        camera_offset_y -= delta_offset * smooth_factor_y;
        if (camera_offset_y <= 0) stop_y = true;
    } else if (camera_offset_y < 0) {
        camera_offset_y += delta_offset * smooth_factor_y;
        if (camera_offset_y >= 0) stop_y = true;
    }

    if (stop_x || stop_y) {
        movement_timer.stop();
        if (stop_x) camera_offset_x = 0;
        if (stop_y) camera_offset_y = 0;
    } else {
        movement_timer.start();
    }
}

void Camera::update() {
    _update_offset();
    if (follow_component.get_x() <= map_size - (width_tiles / 2) &&
        follow_component.get_x() >= (width_tiles / 2)) {
        int new_center_x = follow_component.get_x();
        camera_offset_x += (x_center_tile - new_center_x) * tile_size;
        x_center_tile = new_center_x;
        movement_timer.start();
    }

    if (follow_component.get_y() <= map_size - (height_tiles / 2) &&
        follow_component.get_y() >= (height_tiles / 2)) {
        int new_center_y = follow_component.get_y();
        camera_offset_y += (y_center_tile - new_center_y) * tile_size;
        y_center_tile = new_center_y;
        movement_timer.start();
    }
    
}

void Camera::draw(RenderizableObject *component, int x, int y, int x_tmp_offset,
                  int y_tmp_offset) {
    SDLArea dest =
        _get_render_area(component, x, y, x_tmp_offset, y_tmp_offset);
    component->render(dest);
}

void Camera::render_map_layer(std::vector<Decoration> &layer) {
    for (auto tile = layer.begin(); tile != layer.end(); ++tile) {
        SDLArea dest = _get_render_area((*tile));
        (*tile).render(dest);
    }
}