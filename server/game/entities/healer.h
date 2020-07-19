#ifndef HEALER_H
#define HEALER_H

#include "npc.h"
#include "player.h"

class Healer : public Npc {
   public:
    Healer(EntityId entity_id, nlohmann::json npc_info, Map& map);
    ~Healer();
    /**
     * @brief Restablece la vida del jugador al maximo.
     * En caso de que el jugador este muerto, no hace nada.
     * 
     * @param player 
     */
    void heal(Player* player);
    /**
     * @brief Resucita al jugador luego de un breve tiempo, restableciendo
     * la mana y vida de este, al maximo.
     * 
     * @param player 
     */
    void resuscitate(Player* player);
};

#endif // HEALER_H