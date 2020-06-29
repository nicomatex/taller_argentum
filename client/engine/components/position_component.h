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
    PositionComponent(int x, int y);
    ~PositionComponent();
    void init() override;
    void update() override;
    int get_x();
    int get_y();
    void set_position(int x, int y);
    bool position_initialized();
};

#endif