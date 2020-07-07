#ifndef __UI_EVENT_HANDLER_H
#define __UI_EVENT_HANDLER_H

#include <atomic>

#include "../../../include/network/socket_manager.h"
#include "../../engine/camera.h"
#include "../../game_state_monitor.h"
#include "../../network/event_factory.h"
#include "chat.h"
#include "hud.h"
class UiEventHandler {
   private:
    GameStateMonitor &game_state_monitor;
    SocketManager &socket_manager;
    Hud &hud;
    bool text_input_enabled;
    Camera &camera;
    SDL_Rect main_render_viewport;
    position_t current_target;
    int selected_inventory_slot;
    
   public:
    UiEventHandler(SocketManager &socket_manager,
                   GameStateMonitor &game_state_monitor, Hud &hud,
                   Camera &camera, SDL_Rect main_render_viewport);
    ~UiEventHandler();

    void send_event(const Event &event);

    void handle_quit();
    void handle_keydown_move_up();
    void handle_keydown_move_down();
    void handle_keydown_move_left();
    void handle_keydown_move_right();
    void handle_keydown_return();
    void handle_keydown_backspace();
    void handle_keydown_sound_toggle();
    void handle_keydown_attack();
    void handle_keydown_pickup();

    void handle_keyup_move_up();
    void handle_keyup_move_down();
    void handle_keyup_move_left();
    void handle_keyup_move_right();


    void handle_click(SDL_Event &e);

    void handle();
};

#endif