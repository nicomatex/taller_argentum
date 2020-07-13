#ifndef __RECEIVE_HANDLER_H
#define __RECEIVE_HANDLER_H

#include <atomic>

#include "../../include/blocking_th_event_handler.h"
#include "../../include/event.h"
#include "../chat_buffer.h"
#include "../engine/ECS/entity_manager.h"
#include "../engine/map.h"
#include "../game_state_monitor.h"
#include "../inventory_buffer.h"
#include "../map_change_buffer.h"
#include "../loot_buffer.h"

class ClientReceiveHandler : public BlockingThEventHandler {
   private:
    void handle(Event &ev) override;
    void handle_move(Event &ev);
    void handle_initialization(Event &ev);
    void handle_entity_update(Event &ev);
    void handle_chat_message(Event &ev);
    void handle_map_change(Event &ev);
    void handle_inventory_update(Event &ev);
    void handle_loot_update(Event &ev);
    void handle_incoming_damage(Event &ev);
    void handle_outcoming_damage(Event &ev);
    void handle_outcoming_evaded_damage(Event &ev);
    void handle_incoming_damage_evaded(Event &ev);
    void handle_name_not_found(Event &ev);
    void handle_name_already_online(Event &ev);
    void handle_name_taken(Event &ev);
    
    MapChangeBuffer &map_change_buffer;
    ChatBuffer &chat_buffer;
    InventoryBuffer &inventory_buffer;
    LootBuffer &loot_buffer;
    GameStateMonitor &game_state_monitor;
    // la idea es tener los handlers todos aca

   public:
   /**
    * @brief Objeto manejador de eventos provenientes del servidor.
    * 
    * @param map_change_buffer Buffer de cambio de mapa.
    * @param chat_buffer Buffer de chat.
    * @param inventory_buffer Buffer de inventario.
    * @param loot_buffer Buffer de loot en el mapa.
    * @param game_state_monitor Monitor del estado del juego.
    */
    ClientReceiveHandler(MapChangeBuffer &map_change_buffer,
                         ChatBuffer &chat_buffer,
                         InventoryBuffer &inventory_buffer,
                         LootBuffer &loot_buffer,
                         GameStateMonitor &game_state_monitor);
    ~ClientReceiveHandler();
};

#endif