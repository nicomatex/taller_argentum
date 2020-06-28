#include "sdl_music.h"
#include "sdl_error.h"
#include "sdl_config.h"

SDLMusic::SDLMusic(const std::string& filename){
    this->music = Mix_LoadMUS(filename.c_str());
    if(!this->music){
        throw SDLError(ERR_AUDIOFILE_LOAD);
    }
}

void SDLMusic::play(){
    if(Mix_PausedMusic()){
        Mix_ResumeMusic();
        return;
    }
    /* Se para cualquier musica que se haya estado
    reproduciendo antes.*/
    stop();
    Mix_PlayMusic(music,-1);
}

void SDLMusic::stop(){
    if(Mix_PlayingMusic() != 0){
        Mix_HaltMusic();
    }
}

void SDLMusic::pause(){
    if(Mix_PlayingMusic() != 0){
        Mix_PauseMusic();
    }
}

SDLMusic::~SDLMusic(){
    Mix_FreeMusic(this->music);
}