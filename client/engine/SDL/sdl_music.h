#ifndef __SDL_MUSIC_H
#define __SDL_MUSIC_H

#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

/**
 * @brief Objeto musical de SDL.
 * 
 */
class SDLMusic {
   private:
    Mix_Music* music;

   public:
   /**
    * @brief Construye un nuevo objeto SDLMusic
    * 
    * @param filename Ruta al archivo que contiene la musica.
    */
    SDLMusic(const std::string& filename);
    ~SDLMusic();

    /**
     * @brief Reproduce la musica.
     * @details Si habia otra musica reproduciendose antes, la detiene.
     *
     */
    void play();

	/**
	 * @brief Pausa la musica.
	 * 
	 */
    void pause();

	/**
	 * @brief Detiene la musica.
	 * 
	 */
    void stop();
};

#endif