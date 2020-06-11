#include <iostream>

#include "engine/ECS/component.h"
#include "engine/ECS/component_util.h"
#include "engine/ECS/entity.h"
#include "engine/ECS/entity_factory.h"
#include "engine/ECS/entity_manager.h"
#include "engine/ECS/position_component.h"

int main(void) {
    try {
        EntityManager e_manager;
        EntityFactory e_factory(e_manager);
        Entity& player = e_factory.create_player();
        std::cout << player.has_component<PositionComponent>() << std::endl;
        player.kill();
        e_manager.clean();
        e_manager.update();
        e_manager.draw();
    } catch (std::exception& e) {
        std::cout << "Exception" << std::endl;
    }
    return 0;
    return 0;
}
