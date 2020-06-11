#include "entity_factory.h"
#include "ECS/entity.h"
#include "components/position_component.h"
#include "components/visual_character_component.h"

EntityFactory::EntityFactory(EntityManager &e_manager) :
						     e_manager(e_manager) {}

EntityFactory::~EntityFactory() {}

Entity &EntityFactory::create_player(int head_id, int body_id, int weapon_id, int offhand_id){
	Entity &player = e_manager.create();
	player.add_component<PositionComponent>(10,10);
	player.add_component<VisualCharacterComponent>(head_id,body_id,weapon_id,offhand_id);

	return player;
}