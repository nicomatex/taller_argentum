#ifndef __SDL_MUSIC_H
#define __SDL_MUSIC_H

#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL.h"
#include <string>

class SDLMusic{
    private:
        Mix_Music* music;
    
    public:
        SDLMusic(const std::string& filename);
        ~SDLMusic();

        void play();
        void pause();
        void stop();
};

#endif