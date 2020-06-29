#include "sound_component.h"

#include "../ECS/entity.h"
#include "../resource_manager.h"
#include "visual_character_component.h"

SoundComponent::SoundComponent() {
    step_sound_timer.start();
}

SoundComponent::~SoundComponent() {}

void SoundComponent::update() {
    if (this->entity->get_component<VisualCharacterComponent>().is_moving()) {
        if (step_sound_timer.get_ticks() > 250) {
            ResourceManager::get_instance().get_sound_fx(1).play();
            step_sound_timer.start();
        }
    }
}

void SoundComponent::init() {}