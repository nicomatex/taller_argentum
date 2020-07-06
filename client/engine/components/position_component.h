#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include <mutex>

#include "../ECS/component.h"
#include "../SDL/sdl_timer.h"

class PositionComponent : public Component {
   private:
    int x;
    int y;
    std::mutex m;

    /* Indica si se llamo a set_position al menos una vez. */
    bool initialized;

   public:
    PositionComponent();

    /**
     * @brief Crea un objeto Position Component
     * 
     * @param x X inicial.
     * @param y Y inicial.
     */
    PositionComponent(int x, int y);
    ~PositionComponent();
    void init() override;
    void update() override;

    /**
     * @brief Devuelve la coordenada X.
     * 
     * @return int 
     */
    int get_x();

    /**
     * @brief Devuelve la coordenada Y.
     * 
     * @return int 
     */
    int get_y();

    /**
     * @brief Setea la posicion.
     * 
     * @param x Nueva coordenada X de la posicion.
     * @param y Nueva coordenada Y de la posicion.
     */
    void set_position(int x, int y);

    /**
     * @brief Indica si ya hubo un set_position.
     * 
     * @return true si ya hubo un set_position.
     * @return false si no hubo un set_position.
     */
    bool position_initialized();
};

#endif