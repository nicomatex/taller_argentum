#include "entity_factory.h"
#include "entity.h"
#include "position_component.h"

EntityFactory::EntityFactory(EntityManager &e_manager) :
						     e_manager(e_manager) {}

EntityFactory::~EntityFactory() {}

Entity& EntityFactory::createPlayer() {
	Entity &player = e_manager.create();
	player.addComponent<PositionComponent>();
	//player.addComponent<VisualComponent>();
	//player.addComponent<InputComponent>();
	//player.addComponent<CollisionComponent>();
	return player;
}