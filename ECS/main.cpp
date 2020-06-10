#include <iostream>
#include "component.h"
#include "component_util.h"
#include "entity.h"
#include "entity_manager.h"
#include "position_component.h"
#include "entity_factory.h"

int main(int argc, char const *argv[]) {
	try {
		EntityManager e_manager;
		EntityFactory e_factory(e_manager);
		Entity& player = e_factory.createPlayer();
		std::cout << player.hasComponent<PositionComponent>() << std::endl;
		player.kill();
		e_manager.clean();
		e_manager.update(5);
		e_manager.draw();
	} catch(std::exception &e) {
		std::cout << "Exception" << std::endl;
	}
	return 0;
}