#include "ui_event_handler.h"

#include <algorithm>
#include <iostream>

#include "../../../include/network/socket_exception.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "../../network/event_factory.h"

UiEventHandler::UiEventHandler(SocketManager &socket_manager,
                               GameStateMonitor &game_state_monitor, Hud &hud,
                               Camera &camera)
    : socket_manager(socket_manager),
      hud(hud),
      text_input_enabled(false),
      game_state_monitor(game_state_monitor),
      camera(camera) {
    SDL_StopTextInput();
}

UiEventHandler::~UiEventHandler() {}

void UiEventHandler::send_event(const Event &event) {
    try {
        socket_manager.send(event);
    } catch (std::exception &e) {
        std::cout << "Conexion cerrada inesperadamente!" << std::endl;
        game_state_monitor.quit();
    }
}

void UiEventHandler::handle_keydown_move_up() {
    send_event(EventFactory::movement_event(START, UP));
}

void UiEventHandler::handle_keydown_move_down() {
    send_event(EventFactory::movement_event(START, DOWN));
}

void UiEventHandler::handle_keydown_move_left() {
    send_event(EventFactory::movement_event(START, LEFT));
}

void UiEventHandler::handle_keydown_move_right() {
    send_event(EventFactory::movement_event(START, RIGHT));
}

void UiEventHandler::handle_keyup_move_up() {
    send_event(EventFactory::movement_event(STOP, UP));
}

void UiEventHandler::handle_keyup_move_down() {
    send_event(EventFactory::movement_event(STOP, DOWN));
}

void UiEventHandler::handle_keyup_move_left() {
    send_event(EventFactory::movement_event(STOP, LEFT));
}

void UiEventHandler::handle_keyup_move_right() {
    send_event(EventFactory::movement_event(STOP, RIGHT));
}

void UiEventHandler::handle_keydown_return() {
    hud.chat.toggle();
    if (text_input_enabled) {
        SDL_StopTextInput();
        text_input_enabled = false;
        send_event(EventFactory::chat_event(hud.chat.get_input_and_erase()));
    } else {
        SDL_StartTextInput();
        text_input_enabled = true;
    }
}

void UiEventHandler::handle_keydown_backspace() {
    if (text_input_enabled) hud.chat.input_erase();
}

void UiEventHandler::handle_quit() {
    send_event(EventFactory::disconnect());
    game_state_monitor.quit();
}

void UiEventHandler::handle_keydown_attack() {
    send_event(EventFactory::attack_event());
}

void UiEventHandler::handle_keydown_sound_toggle() {
    static bool sound_enabled = true;
    if (sound_enabled) {
        Mix_VolumeMusic(0);
        Mix_Volume(-1, 0);
        sound_enabled = false;
    } else {
        Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
        Mix_Volume(-1, MIX_MAX_VOLUME / 3);
        sound_enabled = true;
    }
}

void UiEventHandler::handle_click(SDL_Event &e){
    int x,y;
    SDL_GetMouseState(&x,&y);
    position_t tile_clicked = camera.tile_at(x,y);
    std::cout << "Tile clicked: " << tile_clicked.x << " - " << tile_clicked.y << std::endl;
}

void UiEventHandler::handle() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) handle_quit();
        if (e.type == SDL_KEYDOWN) {
            if (e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        handle_keydown_move_up();
                        break;
                    case SDLK_DOWN:
                        handle_keydown_move_down();
                        break;
                    case SDLK_RIGHT:
                        handle_keydown_move_right();
                        break;
                    case SDLK_LEFT:
                        handle_keydown_move_left();
                        break;
                }
            }
            switch (e.key.keysym.sym) {
                case SDLK_BACKSPACE:
                    handle_keydown_backspace();
                    break;
                case SDLK_RETURN:
                    handle_keydown_return();
                    break;
                case SDLK_LCTRL:
                    handle_keydown_attack();
                    break;
                case SDLK_RCTRL:
                    handle_keydown_attack();
                    break;
                case SDLK_m:
                    if (!text_input_enabled) handle_keydown_sound_toggle();
                    break;
            }

        } else if (e.type == SDL_KEYUP) {
            if (e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        handle_keyup_move_up();
                        break;
                    case SDLK_DOWN:
                        handle_keyup_move_down();
                        break;
                    case SDLK_RIGHT:
                        handle_keyup_move_right();
                        break;
                    case SDLK_LEFT:
                        handle_keyup_move_left();
                        break;
                }
            }
        } else if (e.type == SDL_TEXTINPUT) {
            hud.chat.add_characters(e.text.text);
        }else if (e.type == SDL_MOUSEBUTTONUP){
            handle_click(e);
        }
        hud.handle_event(e);
    }
}