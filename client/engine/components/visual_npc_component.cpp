#include "visual_npc_component.h"

#include "../../engine/resource_manager.h"
#include "../ECS/entity.h"
#include "../engine_config.h"
#include "../visual_config.h"

VisualNPCComponent::VisualNPCComponent(int body_id, int speed,
                                       const std::string& name)
    : speed(speed),
      initialized(false),
      body(ResourceManager::get_instance().get_animation_pack("npcs", body_id),
           {0, 0, 0, 0}),
      transition_offset_x(0),
      transition_offset_y(0),
      render_name(name, MONSTER_NAME_COLOR, NAME_FONT_ID, NAME_INFO),
      render_damage("0", DAMAGE_COLOR, DAMAGE_FONT_ID, DAMAGE_INFO),
      recently_damaged(false) {
    int real_width = ResourceManager::get_instance()
                         .get_animation_pack("npcs", body_id)
                         .get_frame_width(DOWN);
    int real_height = ResourceManager::get_instance()
                          .get_animation_pack("npcs", body_id)
                          .get_frame_height(DOWN);

    int arbitrary_width =
        (real_width * SIZE_GRANULARITY * (float)NPC_SIZE_FACTOR) /
        PATTERN_TILE_SIZE;
    int arbitrary_height =
        (real_height * SIZE_GRANULARITY * NPC_SIZE_FACTOR) / PATTERN_TILE_SIZE;

    int offset_x = 0;

    if (arbitrary_width > SIZE_GRANULARITY)
        offset_x = (SIZE_GRANULARITY - arbitrary_width) / 2;

    body.set_visual_info(
        {arbitrary_width, arbitrary_height, offset_x, 0});
}

VisualNPCComponent::~VisualNPCComponent() {}

void VisualNPCComponent::init() {
    /* Se actualiza la posicion de todos los actores para matchear con
la componente de posicion. */
    current_x = entity->get_component<PositionComponent>().get_x();
    current_y = entity->get_component<PositionComponent>().get_y();
}

void VisualNPCComponent::draw(Camera& camera) {
    std::unique_lock<std::recursive_mutex> l(m);
    camera.draw(&body, current_x, current_y, transition_offset_x,
                transition_offset_y);
    camera.draw(&render_name, current_x, current_y, transition_offset_x,
                transition_offset_y);
    if (recently_damaged) {
        camera.draw(&render_damage, current_x, current_y, transition_offset_x,
                    transition_offset_y);
    }
}

void VisualNPCComponent::_update_offset() {
    int movement_transition_time = 1000 / speed;

    int delta_offset = (MOVEMENT_OFFSET * transition_timer.get_ticks());
    delta_offset /= movement_transition_time;

    bool stop_x = false;
    bool stop_y = false;

    float speed_factor_x =
        (float)abs(transition_offset_x) / (float)MOVEMENT_OFFSET;
    if (speed_factor_x < 1) speed_factor_x = 1;

    float speed_factor_y =
        (float)abs(transition_offset_y) / (float)MOVEMENT_OFFSET;
    if (speed_factor_y < 1) speed_factor_y = 1;

    if (transition_offset_x > 0) {
        transition_offset_x -= delta_offset * speed_factor_x;
        if (transition_offset_x <= 0) stop_x = true;
    } else if (transition_offset_x < 0) {
        transition_offset_x += delta_offset * speed_factor_x;
        if (transition_offset_x >= 0) stop_x = true;
    } else if (transition_offset_y > 0) {
        transition_offset_y -= delta_offset * speed_factor_y;
        if (transition_offset_y <= 0) stop_y = true;
    } else if (transition_offset_y < 0) {
        transition_offset_y += delta_offset * speed_factor_y;
        if (transition_offset_y >= 0) stop_x = true;
    }

    if (stop_x || stop_y) {
        transition_timer.stop();
        if (stop_x) transition_offset_x = 0;
        if (stop_y) transition_offset_y = 0;
    } else {
        transition_timer.start();
    }
}

void VisualNPCComponent::_update_animation(int delta_x, int delta_y) {
    if (!transition_timer.is_started()) {
        body.set_move_status(IDLE);
    }

    if (delta_x == 0 && delta_y == 0) return;
    if (!(entity->get_component<PositionComponent>().position_initialized()))
        return;

    transition_offset_x -= delta_x * MOVEMENT_OFFSET;
    transition_offset_y -= delta_y * MOVEMENT_OFFSET;

    body.set_move_status(MOVING);
    transition_timer.start();
}

void VisualNPCComponent::update() {
    std::unique_lock<std::recursive_mutex> l(m);
    /* Se actualiza la posicion de todos los actores para matchear con
    la componente de posicion. */
    int new_x = entity->get_component<PositionComponent>().get_x();
    int new_y = entity->get_component<PositionComponent>().get_y();
    if (initialized) {
        _update_animation(new_x - current_x, new_y - current_y);
        _update_offset();
    } else if (entity->get_component<PositionComponent>()
                   .position_initialized()) {
        initialized = true;
    }
    current_x = new_x;
    current_y = new_y;
    body.update();
    if (recently_damaged) {
        if (damage_render_timer.get_ticks() >= DAMAGE_TEXT_DURATION) {
            recently_damaged = false;
            damage_render_timer.stop();
        }
    }
}

bool VisualNPCComponent::is_moving() {
    return transition_offset_x != 0 || transition_offset_y != 0;
}

void VisualNPCComponent::set_orientation(direction_t new_orientation) {
    std::unique_lock<std::recursive_mutex> l(m);
    body.set_orientation(new_orientation);
}

void VisualNPCComponent::server_update(nlohmann::json update_info) {
    std::unique_lock<std::recursive_mutex> l(m);
    set_orientation(update_info["direction"]);
}

void VisualNPCComponent::display_damage(int damage) {
    render_damage.update_text("-" + std::to_string(damage));
    recently_damaged = true;
    damage_render_timer.start();
}