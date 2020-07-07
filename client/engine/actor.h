#ifndef __ACTOR_H
#define __ACTOR_H

#include "animation_pack.h"
#include "renderizable_object.h"

class AnimationPack;

/**
 * @brief Objeto renderizable que contiene informacion para las 
 * cuatro orientaciones posibles, y los dos estados de movimiento.
 * 
 */
class Actor : public RenderizableObject {
   private:
    AnimationPack animation_pack;
    direction_t orientation;
    movement_status_t movement_status;

    /* Actualiza el estado de movimiento. */
    void _update_status();

    bool is_empty;

   public:
    /**
     * @brief Crea un objeto Actor
     * 
     * @param animation_pack Pack de animacion asociado al actor.
     * @param visual_info Struct de informacion visual.
     */
    Actor(AnimationPack& animation_pack, visual_info_t visual_info);


    /**
     * @brief Establece una nueva orientacion.
     * 
     * @param new_direction Nueva orientacion del actor.
     */
    void set_orientation(direction_t new_direction);

    /**
     * @brief Establece el estado de movimiento.
     * 
     * @param new_movement_status Nuevo estado de movimiento.
     */
    void set_move_status(movement_status_t new_movement_status);

    /**
     * @brief Devuelve la direccion.
     * 
     * @return direction_t 
     */
    direction_t get_direction();

    /**
     * @brief Devuelve el estatus de movimiento.
     * 
     * @return movement_status_t 
     */
    movement_status_t get_movement_status();

    /**
     * @brief Renderiza el objecto en pantalla.
     * 
     * @param dest Cuadro donde se va a renderizar el objeto.
     */
    void render(SDL_Rect dest) override;

    void update() override;

    Actor(const Actor& other);
    Actor& operator=(const Actor& other);
};

#endif
