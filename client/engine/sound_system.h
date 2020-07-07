#ifndef __SOUND_SYSTEM_H
#define __SOUND_SYSTEM_H
#include "SDL/sdl_timer.h"

/**
 * @brief Singleton para el sistema de sonido del juego.
 * 
 */
class SoundSystem {
   private:
    SoundSystem();
    int max_concurrent_sounds;
    int currently_playing_sounds;
    SDLTimer sound_timer;

   public:
    static SoundSystem& get_instance();
    ~SoundSystem();

    /**
     * @brief Reproduce musica.
     *
     * @details Si ya hay musica reproduciendo, para la musica anterior
     * antes de reproducir la nueva.
     *
     * @param id id de la cancion a reproducir.
     */
    void play_music(int id);

    /**
     * @brief Reproduce un efecto de sonido.
     *
     * @details Se limita la cantidad de efectos que se pueden reproducir
     * en simultaneo.
     *
     * @param id id del efecto de sonido.
     */
    void play_ui_sfx(int id);

    /**
     * @brief Reproduce un efecto de sonido.
     *
     * @details Limita la cantidad de efectos de sonido del juego (pasos,
     * golpes, etc) que se pueden oir en simultaneo.
     *
     * @param id
     */
    void play_game_sfx(int id);

    /**
     * @brief Indica si hay musica reproduciendose.
     *
     * @return true Si hay musica reproduciendose.
     * @return false Si no hay musica reproduciendose.
     */
    bool music_playing();

    /**
     * @brief Establece el volumen tanto de los efectos de sonido como de la
     * musica.
     *
     * @param volume Nuevo volumen. Debe ir entre 0 y 128. (definido en
     * MIX_MAX_VOLUME)
     */
    void set_master_volume(int volume);

    /**
     * @brief Establece el volumen de la musica.
     *
     * @param volume Nuevo volumen. Debe ir entre 0 y 128. (definido en
     * MIX_MAX_VOLUME)
     */
    void set_music_volume(int volume);

    /**
     * @brief Establece el volumen de los efectos de sonido.
     *
     * @param volume Nuevo volumen. Debe ir entre 0 y 128. (definido en
     * MIX_MAX_VOLUME)
     */
    void set_sfx_volume(int volume);
    
    
};

#endif