#ifndef __GAME_CLIENT_H
#define __GAME_CLIENT_H

/* ----- Includes ----- */
#include <unordered_map>

#include "engine/ECS/entity_manager.h"
#include "engine/SDL/sdl_texture.h"
#include "engine/SDL/sdl_texture_loader.h"
#include "engine/SDL/sdl_window.h"
#include "engine/actor.h"
#include "engine/animation_pack.h"
#include "engine/entity_factory.h"
#include <atomic>

/* Interfaz de la clase */
class GameClient {
   private:
    SDLWindow main_window;
    EntityManager entity_manager;
    EntityFactory entitiy_factory;
    void _update_game(SDL_Event &e);
    void _update_components(SDL_Event &e, Entity &player);
    std::atomic_bool running;
    void _poll_events();

   public:
    GameClient(const std::string &texture_index_file,
               const std::string &sprite_index_file);
    ~GameClient();
    void run();
};

#endif