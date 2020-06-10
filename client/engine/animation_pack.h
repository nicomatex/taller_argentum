#ifndef __ANIMATION_PACK_H
#define __ANIMATION_PACK_H

#include "SDL/sdl_animated_sprite.h"
#include "SDL/sdl_area.h"

enum Orientation { UP, DOWN, LEFT, RIGHT };
enum MovementStatus { MOVING, IDLE };

class AnimationPack {
   private:
    /* Sprites de movimiento. */
    SDLSprite up_move_sprite;
    SDLSprite down_move_sprite;
    SDLSprite right_move_sprite;
    SDLSprite left_move_sprite;

    /* Sprites quietos */
    SDLSprite up_idle_sprite;
    SDLSprite down_idle_sprite;
    SDLSprite right_idle_sprite;
    SDLSprite left_idle_sprite;

   public:
    AnimationPack(SDLSprite &&up_move_sprite, SDLSprite &&down_move_sprite,
                  SDLSprite &&left_move_sprite, SDLSprite &&right_move_sprite, 
                  SDLSprite &&up_idle_sprite, SDLSprite &&down_idle_sprite,
                  SDLSprite &&left_idle_sprite, SDLSprite &&right_idle_sprite);
    ~AnimationPack();

    void render(Orientation orientation, MovementStatus status, const SDLArea &dest);
    
    /* No se permite la construccion por copia. */
    AnimationPack(const AnimationPack &other) = delete;
    AnimationPack& operator=(AnimationPack &other) = delete;

    /* Constructor y asginador por movimiento. */
    AnimationPack(AnimationPack &&other);
    AnimationPack& operator=(AnimationPack &&other);
};

#endif
