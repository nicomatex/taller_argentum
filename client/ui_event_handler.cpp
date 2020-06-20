#include "ui_event_handler.h"

#include "SDL2/SDL.h"
#include "event_factory.h"

UiEventHandler::UiEventHandler(std::atomic_bool &running,
                               SocketManager &socket_manager)
    : running(running), socket_manager(socket_manager), chat(NULL) {}

UiEventHandler::~UiEventHandler() {}

void UiEventHandler::handle_keydown_move_up() {
    socket_manager.send(event_factory.movement_event(START, UP));
}

void UiEventHandler::handle_keydown_move_down() {
    socket_manager.send(event_factory.movement_event(START, DOWN));
}

void UiEventHandler::handle_keydown_move_left() {
    socket_manager.send(event_factory.movement_event(START, LEFT));
}

void UiEventHandler::handle_keydown_move_right() {
    socket_manager.send(event_factory.movement_event(START, RIGHT));
}

void UiEventHandler::handle_keyup_move_up() {
    socket_manager.send(event_factory.movement_event(STOP, UP));
}

void UiEventHandler::handle_keyup_move_down() {
    socket_manager.send(event_factory.movement_event(STOP, DOWN));
}

void UiEventHandler::handle_keyup_move_left() {
    socket_manager.send(event_factory.movement_event(STOP, LEFT));
}

void UiEventHandler::handle_keyup_move_right() {
    socket_manager.send(event_factory.movement_event(STOP, RIGHT));
}

void UiEventHandler::handle() {
    static bool text_input_enabled = false;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) running = false;
        if (e.type == SDL_KEYDOWN) {
            if(e.key.repeat == 0){
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
            switch(e.key.keysym.sym){
                case SDLK_BACKSPACE:
                    if(text_input_enabled) chat->input_erase();
                    break;
                case SDLK_RETURN:
                    chat->toggle();
                    if(text_input_enabled){
                        SDL_StopTextInput();
                        text_input_enabled = false;
                        chat->print_line(chat->get_input_and_erase());
                    }else{
                        SDL_StartTextInput();
                        text_input_enabled = true;
                    }
            }
            
        } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
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
        } else if(e.type == SDL_TEXTINPUT){
            chat->add_characters(e.text.text);
        }
    }
}

void UiEventHandler::attach_chat(Chat *new_chat) { chat = new_chat; }