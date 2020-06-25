#ifndef __VISUAL_CHARACTER_COMPONENT
#define __VISUAL_CHARACTER_COMPONENT
#include <unordered_map>

#include "../../../include/types.h"
#include "../ECS/component.h"
#include "../actor.h"
#include "../camera.h"

typedef std::unordered_map<std::string, Actor> Parts;
typedef std::unordered_map<std::string, int> PartIds;

class VisualCharacterComponent : public Component {
   private:
    Camera *camera;
    Parts parts;
    PartIds part_ids;
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
    VisualCharacterComponent(int head_id, int body_id, int weapon_id,
                             int shield_id, int helmet_id, int armor_id,
                             int speed);
    ~VisualCharacterComponent();
    Actor &get_part(const std::string &type);
    void bind_to_camera(Camera &bind_camera);

    void server_update(nlohmann::json update_info);

    void set_part(const std::string &type, const std::string &texture_family,
                  int new_part_id, visual_info_t visual_info);

    void set_orientation(direction_t new_orientation);
    void init() override;
    void update() override;
    void draw(Camera &camera);
};

#endif