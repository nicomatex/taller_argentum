#ifndef __GAME_CLIENT_H
#define __GAME_CLIENT_H

/* ----- Includes ----- */
#include <unordered_map>

#include "actor.h"
#include "animation_pack.h"
#include "include/SDL/sdl_texture.h"
#include "include/SDL/sdl_texture_loader.h"
#include "include/SDL/sdl_window.h"

/* ----- Tipos y forward declarations ----- */
typedef std::unordered_map<std::string,
                           std::unordered_map<int, SDLTexture>>
    TextureMap;

typedef std::unordered_map<std::string,
                           std::unordered_map<int, AnimationPack>>
    AnimationPackMap;

typedef std::unordered_map<std::string,
                           std::unordered_map<int, SDLSprite>>
    SpriteMap;

/* Interfaz de la clase */
class GameClient {
   private:
    TextureMap texture_map;
    AnimationPackMap animation_pack_map;
    SpriteMap sprite_map;

    SDLWindow main_window;

    /* Realiza la carga de texturas indexadas en el texture_index_file, llenando
    el texture_map. */
    void _load_textures(SDLTextureLoader &loader,
                        const std::string &texture_index_file);

    /* Genera las animaciones indicadas en el sprite_index_file, llenando
    el animation_pack_map y el sprite_map */
    void _load_animations(const std::string &sprite_index_file);

    void _update_game(SDL_Event &e);
    void _update_components(SDL_Event &e, Actor &player);

   public:
    GameClient(const std::string &texture_index_file,
               const std::string &sprite_index_file);
    ~GameClient();
    void run();
};

#endif