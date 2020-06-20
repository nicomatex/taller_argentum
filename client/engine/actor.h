#ifndef __ACTOR_H
#define __ACTOR_H

#include "animation_pack.h"
#include "renderizable_object.h"

class AnimationPack;

class Actor : public RenderizableObject {
   private:
    AnimationPack &animation_pack;
    direction_t orientation;
    movement_status_t movement_status;

    /* Actualiza el estado de movimiento. */
    void _update_status();

    bool is_empty;

   public:
    Actor(AnimationPack &animation_pack, int width, int height,
          int x_offset, int y_offset);

    /* Establece la nueva orientacion.*/
    void set_orientation(direction_t new_direction);

    /* Establece el nuevo estado de movimiento.*/
    void set_move_status(movement_status_t new_movement_status);

    /* Renderiza el objeto en pantalla. */
    void render(SDL_Rect dest) override;

    /* Getters para el offset total en centesimas de tile. */
    int get_x_offset() const override;
    int get_y_offset() const override;

    void update() override;
};

#endif
