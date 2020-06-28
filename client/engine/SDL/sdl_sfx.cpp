#include "sdl_sfx.h"
#include "sdl_error.h"
#include "sdl_config.h"

SDLSoundFx::SDLSoundFx(const std::string& filename){
    this->sound = Mix_LoadWAV(filename.c_str());
    if(!this->sound){
        throw SDLError(ERR_AUDIOFILE_LOAD); 
    }
}

SDLSoundFx::~SDLSoundFx(){
    Mix_FreeChunk(sound);
}

void SDLSoundFx::play(){
    Mix_PlayChannel(-1,sound,0);
}