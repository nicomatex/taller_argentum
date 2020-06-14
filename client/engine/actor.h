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
    SDLTimer transition_timer;

    /* Actualiza el offset de renderizacion. */
    void _update_offset();

    /* Actualiza el estado de movimiento. */
    void _update_status();

    int transition_offset_x;
    int transition_offset_y;

    bool is_empty;

   public:
    Actor(AnimationPack &animation_pack, int x, int y, int width, int height,
          int x_offset, int y_offset);

    /* Establece la nueva orientacion.*/
    void set_orientation(direction_t new_direction);

    /* Establece el nuevo estado de movimiento.*/
    void set_move_status(movement_status_t new_movement_status);

    /* Establece la nueva posicion del actor. Si animation es true, la
    transicion se hace de forma suave, disparando la animacion correspondiente
    en el actor. */
    void set_position(int new_x, int new_y, bool animation);

    /* Renderiza el objeto en pantalla. */
    void render(const SDLArea &dest) override;

    /* Getters para el offset total en centesimas de tile. */
    int get_x_offset() const override;
    int get_y_offset() const override;

    /* Getters para el offset de transicion en centesimas de tile. */
    int get_transition_offset_x() const override;
    int get_transition_offset_y() const override;

    bool is_transitioning() const override;

    void update() override;
};

#endif
