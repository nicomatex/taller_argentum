#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../../include/nlohmann/json.hpp"
#include "ECS/entity.h"
#include "ECS/entity_manager.h"

/**
 * @brief Fabrica de entidades.
 * 
 */
class EntityFactory {
   private:
   public:
    /**
     * @brief Crea un objeto player
     *
     * @param entity_info json con informacion para crear el jugador.
     * @return Entity&
     */
    static Entity &create_player(nlohmann::json entity_info);

    /**
     * @brief Crea un objeto npc
     * 
     * @param entity json con informacion para crear el NPC.
     * @return Entity& 
     */
    static Entity &create_npc(nlohmann::json entity);
};

#endif  // ENTITY_FACTORY_H