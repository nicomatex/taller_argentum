#include "sound_component.h"

#include "../ECS/entity.h"
#include "../resource_manager.h"
#include "visual_character_component.h"
#include "../sound_system.h"

SoundComponent::SoundComponent() {
    step_sound_timer.start();
}

SoundComponent::~SoundComponent() {}

void SoundComponent::update() {
    if (this->entity->get_component<VisualCharacterComponent>().is_moving()) {
        if (step_sound_timer.get_ticks() > 250) {
            SoundSystem::get_instance().play_game_sfx(1);
            step_sound_timer.start();
        }
    }
}

void SoundComponent::init() {}