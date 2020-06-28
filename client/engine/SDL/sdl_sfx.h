#ifndef __SDL_SFX_H
#define __SDL_SFX_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include <string>

class SDLSoundFx{
    private:
        Mix_Chunk *sound;
    
    public:
        SDLSoundFx(const std::string& filename);
        ~SDLSoundFx();

        void play();
};

#endif