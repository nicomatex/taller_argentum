#include "entity_factory.h"

#include "ECS/entity.h"
#include "components/position_component.h"
#include "components/visual_character_component.h"

Entity &EntityFactory::create_player(unsigned int entity_id, int head_id,
                                     int body_id, int weapon_id,
                                     int offhand_id) {
    Entity &player = EntityManager::get_instance().create(entity_id);
    player.add_component<PositionComponent>(10, 10);
    player.add_component<VisualCharacterComponent>(head_id, body_id, weapon_id,
                                                   offhand_id,4);
    std::cout << "Added player with entity_id " << entity_id << std::endl;
    return player;
}