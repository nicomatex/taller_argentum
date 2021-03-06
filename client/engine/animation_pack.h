#ifndef __ANIMATION_PACK_H
#define __ANIMATION_PACK_H

#include "SDL/sdl_animated_sprite.h"

#ifndef DIRECTION_T
#define DIRECTION_T
enum direction_t { UP, DOWN, LEFT, RIGHT };
#endif

enum movement_status_t { MOVING, IDLE };

/**
 * @brief Wrapper de sprites de un mismo conjunto.
 * 
 */
class AnimationPack {
   private:
    /* Sprites de movimiento. */
    SDLSprite up_move_sprite;
    SDLSprite down_move_sprite;
    SDLSprite left_move_sprite;
    SDLSprite right_move_sprite;

    /* Sprites quietos */
    SDLSprite up_idle_sprite;
    SDLSprite down_idle_sprite;
    SDLSprite left_idle_sprite;
    SDLSprite right_idle_sprite;

   public:
    AnimationPack(SDLSprite &up_move_sprite, SDLSprite &down_move_sprite,
                  SDLSprite &left_move_sprite, SDLSprite &right_move_sprite, 
                  SDLSprite &up_idle_sprite, SDLSprite &down_idle_sprite,
                  SDLSprite &left_idle_sprite, SDLSprite &right_idle_sprite);
    ~AnimationPack();

    void render(direction_t direction, movement_status_t status, SDL_Rect dest);

    /**
     * @brief Devuelve el ancho en pixeles de un cuadro de la animacion.
     * 
     * @param direction Direccion para la cual se desea conocer el ancho del cuadro.
     * @return int 
     */
    int get_frame_width(direction_t direction);

    /**
     * @brief Devuelve el alto en pixeles de un cuadro de la animacion.
     * 
     * @param direction Direccion para la cual se desea conocer el alto del cuadro.
     * @return int 
     */
    int get_frame_height(direction_t direction);

    /* Constructor y asignador por copia. */
    AnimationPack(const AnimationPack &other);
    AnimationPack& operator=(const AnimationPack &other);

    /* Constructor y asginador por movimiento. */
    AnimationPack(AnimationPack &&other);
    AnimationPack& operator=(AnimationPack &&other);
};

#endif
