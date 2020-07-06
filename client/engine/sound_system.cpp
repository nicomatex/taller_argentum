#include "sound_system.h"

#include "engine_config.h"
#include "resource_manager.h"

SoundSystem::SoundSystem()
    : max_concurrent_sounds(MAX_CONCURRENT_SOUNDS),
      currently_playing_sounds(0) {
    sound_timer.start();
}

SoundSystem& SoundSystem::get_instance() {
    static SoundSystem instance;
    return instance;
}

SoundSystem::~SoundSystem(){}

void SoundSystem::play_music(int id) {
    ResourceManager::get_instance().get_music(id).play();
}

void SoundSystem::play_ui_sfx(int id) {
    ResourceManager::get_instance().get_sound_fx(id).play();
}

void SoundSystem::play_game_sfx(int id) {
    if (sound_timer.get_ticks() >= SOUND_TIMEOUT &&
        currently_playing_sounds > 0) {
        currently_playing_sounds -= sound_timer.get_ticks() / SOUND_TIMEOUT;
        if (currently_playing_sounds < 0) currently_playing_sounds = 0;
        sound_timer.start();
    }
    if (currently_playing_sounds < max_concurrent_sounds) {
        ResourceManager::get_instance().get_sound_fx(id).play();
        ++currently_playing_sounds;
    }
}


void SoundSystem::set_master_volume(int volume){
    set_music_volume(volume);
    set_sfx_volume(volume);
}

void SoundSystem::set_sfx_volume(int volume){
    if(volume < 0) volume = 0;
    if(volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
    Mix_Volume(-1,volume);
}

void SoundSystem::set_music_volume(int volume){
    if(volume < 0) volume = 0;
    if(volume > MIX_MAX_VOLUME) volume = MIX_MAX_VOLUME;
    Mix_VolumeMusic(volume);
}


bool SoundSystem::music_playing(){
    return Mix_PlayingMusic();
}