#include "entity_factory.h"
#include "entity.h"
#include "position_component.h"

EntityFactory::EntityFactory(EntityManager &e_manager) :
						     e_manager(e_manager) {}

EntityFactory::~EntityFactory() {}

Entity& EntityFactory::create_player() {
	Entity &player = e_manager.create();
	player.add_component<PositionComponent>();
	//player.addComponent<VisualComponent>();
	//player.addComponent<InputComponent>();
	//player.addComponent<CollisionComponent>();
	return player;
}