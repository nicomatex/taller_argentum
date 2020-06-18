#ifndef __VISUAL_CHARACTER_COMPONENT
#define __VISUAL_CHARACTER_COMPONENT
#include <unordered_map>
#include "../ECS/component.h"
#include "../actor.h"
#include "../camera.h"

typedef std::unordered_map<std::string,Actor> Parts;

class VisualCharacterComponent : public Component {
   private:
    Camera* camera;
    Parts parts;
    std::mutex m;
    int transition_offset_x;
    int transition_offset_y;
    SDLTimer transition_timer;
    /* Actualiza el offset de renderizacion. */
    void _update_offset();
    void _update_animation(int delta_x, int delta_y);
    int current_x;
    int current_y;
    int speed; //En tiles/segundo.
    
   public:

    VisualCharacterComponent(int head_id, int body_id, int weapon_id, int offhand_id, int speed);
    ~VisualCharacterComponent();
    Actor &get_part(const std::string& type);
    void bind_to_camera(Camera &bind_camera);
	void set_head(int new_head_id);
    void set_body(int new_body_id);
    //TODO: Implementar set_weapon y set_offhand.
    void init() override;
	void update() override;
	void draw() override;

};

#endif