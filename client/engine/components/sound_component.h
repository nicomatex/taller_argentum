#ifndef __SOUND_COMPONENT_H
#define __SOUND_COMPONENT_H

#include "../ECS/component.h"
#include "../SDL/sdl_timer.h"

/**
 * @brief Componente de sonido de los personajes.
 * 
 */
class SoundComponent : public Component {
   private:
    SDLTimer step_sound_timer;

   public:
    SoundComponent();
    ~SoundComponent();

    void update() override;
    void init() override;
};

#endif