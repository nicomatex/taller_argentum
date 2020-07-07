#ifndef __SDL_SPRITE_H
#define __SDL_SPRITE_H

#include <functional>

#include "../../../include/nlohmann/json.hpp"
#include "sdl_texture.h"
#include "sdl_timer.h"

/**
 * @brief Sprite animada de SDL.
 * 
 */
class SDLSprite {
   private:
    std::reference_wrapper<SDLTexture> texture;
    int nframes;
    int current_frame;
    int base_y;
    int base_x;
    int frame_width;
    int frame_height;
    SDLTimer timer;
    uint32_t time_between_frames;

   public:
    /**
     * @brief Construye un objeto SDLSprite
     *
     * @param texture Referencia a la textura con todos los cuadros de la sprite
     * @param nframes Cantidad de cuadros de la animacion
     * @param fps Velocidad en cuadros por segundo a la cual debe ser
     * reproducida
     * @param base_x Origen X de la sprite en la textura
     * @param base_y Origen Y de la sprite en la textura
     * @param w Ancho de cada cuadro
     * @param h Alto de cada cuadro
     */
    SDLSprite(SDLTexture &texture, int nframes, int fps, int base_x, int base_y,
              int w, int h);

    /**
     * @brief Construye un objeto SDLSprite
     *
     * @param texture Referencia a la textura con todos los cuadros de la
     * sprite.
     * @param sprite_info json con toda la informacion de la t extura
     * en formato {"nframes":n,"fps":n,"base x":n, "base y":n, "frame width":n,
     * "frame width":n}
     */
    SDLSprite(SDLTexture &texture, nlohmann::json sprite_info);

    ~SDLSprite();

    /**
     * @brief Constructor por copia
     *
     * @param other Otra sprite.
     */
    SDLSprite(const SDLSprite &other);
    SDLSprite &operator=(const SDLSprite &other);

    /* Constructor y asginador por movimiento. */
    SDLSprite(SDLSprite &&other);
    SDLSprite &operator=(SDLSprite &&other);

    /**
     * @brief Renderiza la sprite en pantalla, segun el cuadro actual.
     * @details Cada llamado consecutivo a render incrementa un contador
     * interno segun el tiempo transcurrido desde el ultimo render, y
     * en caso de ser necesario actualiza el cuadro actual del sprite, para
     * garantizar que la animacion se reproduzca a la velocidad indicada.
     *
     *
     * @param dest Rectangulo SDL de destino en la pantalla
     */
    void render(SDL_Rect dest);

    /**
     * @brief Devuelve el ancho de un cuadro del sprite.
     * 
     * @return int 
     */
    int get_frame_width();

    /**
     * @brief Devuelve el alto de un cuadro del sprite.
     * 
     * @return int 
     */
    int get_frame_height();
};
#endif