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
   public:

    VisualCharacterComponent(int head_id, int body_id, int weapon_id, int offhand_id);
    ~VisualCharacterComponent();
    Actor &get_part(const std::string& type);
    void bind_to_camera(Camera &bind_camera);
	void init() override;
	void update() override;
	void draw() override;
};

#endif