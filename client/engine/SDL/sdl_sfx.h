#ifndef __SDL_SFX_H
#define __SDL_SFX_H

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

/**
 * @brief Objeto de efecto de sonido de SDL.
 * 
 */
class SDLSoundFx {
   private:
    Mix_Chunk* sound;

   public:
    /**
     * @brief Construye un nuevo objeto SDLSoundFx
     *
     * @param filename
     */
    SDLSoundFx(const std::string& filename);
    ~SDLSoundFx();

    /**
     * @brief Reproduce el efecto de sonido.
     * 
     */
    void play();
};

#endif