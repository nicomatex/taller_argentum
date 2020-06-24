#ifndef __VISUAL_CHARACTER_COMPONENT
#define __VISUAL_CHARACTER_COMPONENT
#include <unordered_map>

#include "../ECS/component.h"
#include "../actor.h"
#include "../camera.h"
#include "../../../include/types.h"

typedef std::unordered_map<std::string, Actor> Parts;

class VisualCharacterComponent : public Component {
   private:
    Camera *camera;
    Parts parts;
    int transition_offset_x;
    int transition_offset_y;
    SDLTimer transition_timer;
    /* Actualiza el offset de renderizacion. */
    void _update_offset();
    void _update_animation(int delta_x, int delta_y);
    int current_x;
    int current_y;
    int speed;  // En tiles/segundo.

    int head_id;
    int body_id;
    int helmet_id;
    int weapon_id;
    int shield_id;
    int armor_id;
    // Eventualmente de las demas partes

    std::mutex m;

   public:
    VisualCharacterComponent(int head_id, int body_id, int weapon_id,
                             int shield_id, int helmet_id,int armor_id, int speed);
    ~VisualCharacterComponent();
    Actor &get_part(const std::string &type);
    void bind_to_camera(Camera &bind_camera);

    void set_head(int new_head_id);
    void set_body(int new_body_id);
    void set_helmet(int new_helmet_id);
    void set_weapon(int new_weapon_id);
    void set_shield(int new_shield_id);
    void set_armor(int new_armor_id);
    
    void set_orientation(direction_t new_orientation);
    void init() override;
    void update() override;
    void draw(Camera &camera);
};

#endif