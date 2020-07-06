#include "entity_factory.h"

#include "entities/components/position_component.h"
#include "entities/entity.h"

EntityFactory::EntityFactory(EntityManager &e_manager) : e_manager(e_manager) {}

EntityFactory::~EntityFactory() {}

Entity &EntityFactory::create_player() {
    Entity &player = e_manager.create();
    player.add_component<PositionComponent>();
    // player.addComponent<VisualComponent>();
    // player.addComponent<InputComponent>();
    // player.addComponent<CollisionComponent>();
    return player;
}