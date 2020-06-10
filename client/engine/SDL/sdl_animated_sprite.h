#ifndef __SDL_SPRITE_H
#define __SDL_SPRITE_H

#include "sdl_area.h"
#include "sdl_texture.h"
#include "sdl_timer.h"
#include "../json.hpp"
#include <functional>

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
    /* Recibe una referencia a una textura, la cantidad de frames de las cuales
    esta compuesta la animacion, los cuadros por segundo a los cuales debe reproducirse
    la altura base a la cual comienza la sprite en la textura, el ancho y el alto de 
    cada cuadro, y el cuadro a renderizar cambia cada ciertos intervalos de tiempo, 
    asegurandose de que se rendericen como maximo fps cuadros del sprite por segundo (pueden
    ser menos). */
    SDLSprite(SDLTexture &texture, int nframes, int fps, int base_x, int base_y, int w,
              int h);
    SDLSprite(SDLTexture &texture,nlohmann::json sprite_info);

    ~SDLSprite();

    /* Constructor por copia */
    SDLSprite(const SDLSprite &other);
    SDLSprite& operator=(const SDLSprite &other);

    /* Constructor y asginador por movimiento. */
    SDLSprite(SDLSprite &&other);
    SDLSprite& operator=(SDLSprite &&other);

    /* Renderiza la sprite en el area de destino del renderer. */
    void render(const SDLArea &dest);
};
#endif