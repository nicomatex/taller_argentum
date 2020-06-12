#include "visual_character_component.h"

#include "../ECS/entity.h"
#include "../resource_manager.h"
#include "../visual_config.h"
#include "position_component.h"

VisualCharacterComponent::VisualCharacterComponent(int head_id, int body_id,
                                                   int weapon_id,
                                                   int offhand_id) {
    if (head_id != 0) {
        Actor head(ResourceManager::get_instance().get_animation_pack("heads",
                                                                      head_id),
                   0, 0, HEAD_WIDTH, HEAD_HEIGHT, HEAD_OFFSET_X, HEAD_OFFSET_Y);
        parts.insert(std::make_pair("head", head));
    }
    if (body_id != 0) {
        Actor body(ResourceManager::get_instance().get_animation_pack("bodies",
                                                                      body_id),
                   0, 0, BODY_WIDTH, BODY_HEIGHT, BODY_OFFSET_X, BODY_OFFSET_Y);
        parts.insert(std::make_pair("body", body));
    }
}

void VisualCharacterComponent::init() {
    /* Se actualiza la posicion de todos los actores para matchear con
la componente de posicion. */
    int x = entity->get_component<PositionComponent>().get_x();
    int y = entity->get_component<PositionComponent>().get_y();
    for (auto& part : parts) {
        part.second.set_position(x, y, false);
    }
}

void VisualCharacterComponent::update() {
    /* Se actualiza la posicion de todos los actores para matchear con
    la componente de posicion. */
    int x = entity->get_component<PositionComponent>().get_x();
    int y = entity->get_component<PositionComponent>().get_y();
    for (auto& part : parts) {
        part.second.set_position(x, y, true);
        part.second.update();
    }
}

void VisualCharacterComponent::set_head(int new_head_id) {
    int player_x = entity->get_component<PositionComponent>().get_x();
    int player_y = entity->get_component<PositionComponent>().get_y();

    Actor head(ResourceManager::get_instance().get_animation_pack("heads",
                                                                  new_head_id),
               player_x, player_y, HEAD_WIDTH, HEAD_HEIGHT, HEAD_OFFSET_X,
               HEAD_OFFSET_Y);
    parts.erase("head");
    parts.insert(std::make_pair("head", head));
}

void VisualCharacterComponent::set_body(int new_body_id) {
    int player_x = entity->get_component<PositionComponent>().get_x();
    int player_y = entity->get_component<PositionComponent>().get_y();

    Actor body(
        ResourceManager::get_instance().get_animation_pack("bodies", new_body_id),
        player_x, player_y, BODY_WIDTH, BODY_HEIGHT, BODY_OFFSET_X,
        BODY_OFFSET_Y);
    parts.erase("body");
    parts.insert(std::make_pair("body", body));
}

void VisualCharacterComponent::draw() {
    for (auto& it : parts) {
        camera->draw(&(it.second));
    }
}

Actor& VisualCharacterComponent::get_part(const std::string& type) {
    return parts.at(type);
}

VisualCharacterComponent::~VisualCharacterComponent() {}

void VisualCharacterComponent::bind_to_camera(Camera& bind_camera) {
    camera = &bind_camera;
}