#ifndef __ACTOR_H
#define __ACTOR_H

#include "animation_pack.h"
#include "visual_component.h"

class Actor : public VisualComponent {
   private:
    AnimationPack animation_pack;
    Orientation orientation;
    MovementStatus movement_status;
    SDLTimer offset_timer;
    
    /* Actualiza el offset de renderizacion. */
    void _update_offset();

    /* Actualiza el estado de movimiento. */
    void _update_status();

   public:
    Actor(AnimationPack &&animation_pack, int x, int y, int width, int height);

    /* Establece la nueva orientacion.*/
    void set_orientation(Orientation new_orientation);

    /* Establece el nuevo estado de movimiento.*/
    void set_move_status(MovementStatus new_movement_status);

    /* Mueve el actor step tiles hacia la orientacion indicada, actualizando
    la orientacion, el move status y el offset de renderizacion. */
    void move(Orientation orientation, int steps);

    /* Renderiza el objeto en pantalla. */
    void render(const SDLArea &dest) override;

};

#endif
