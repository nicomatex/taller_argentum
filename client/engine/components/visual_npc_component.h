#ifndef __VISUAL_NPC_COMPONENT_H
#define __VISUAL_NPC_COMPONENT_H

#include "../../../include/types.h"
#include "../../../include/nlohmann/json.hpp"
#include "../ECS/component.h"
#include "../actor.h"
#include "../camera.h"

class VisualNPCComponent : public Component {
   private:
    Camera *camera;
    Actor body;
    int transition_offset_x;
    int transition_offset_y;
    SDLTimer transition_timer;
    /* Actualiza el offset de renderizacion. */
    void _update_offset();
    void _update_animation(int delta_x, int delta_y);
    int current_x;
    int current_y;
    int speed;  // En tiles/segundo.
    
    /* Indica si ya se recibio el primer mensaje de actualizacion de posicion.*/
    bool initialized;
    std::recursive_mutex m;

   public:
    VisualNPCComponent(int body_id, int speed);
    ~VisualNPCComponent();

    void set_orientation(direction_t new_orientation);
    void init() override;
    void update() override;
    void draw(Camera &camera);

    void server_update(nlohmann::json update_info);

    bool is_moving();
};

#endif