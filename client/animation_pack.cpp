#include "animation_pack.h"

AnimationPack::AnimationPack(
    SDLSprite &&up_move_sprite, SDLSprite &&down_move_sprite,
    SDLSprite &&left_move_sprite, SDLSprite &&right_move_sprite,
    SDLSprite &&up_idle_sprite, SDLSprite &&down_idle_sprite,
    SDLSprite &&left_idle_sprite, SDLSprite &&right_idle_sprite)
    : up_move_sprite(std::move(up_move_sprite)),
      down_move_sprite(std::move(down_move_sprite)),
      left_move_sprite(std::move(left_move_sprite)),
      right_move_sprite(std::move(right_move_sprite)),
      up_idle_sprite(std::move(up_idle_sprite)),
      down_idle_sprite(std::move(down_idle_sprite)),
      left_idle_sprite(std::move(left_idle_sprite)),
      right_idle_sprite(std::move(right_idle_sprite)) {}

AnimationPack::AnimationPack(AnimationPack &&other)
    : up_move_sprite(std::move(other.up_move_sprite)),
      down_move_sprite(std::move(other.down_move_sprite)),
      left_move_sprite(std::move(other.left_move_sprite)),
      right_move_sprite(std::move(other.right_move_sprite)),
      up_idle_sprite(std::move(other.up_idle_sprite)),
      down_idle_sprite(std::move(other.down_idle_sprite)),
      left_idle_sprite(std::move(other.left_idle_sprite)),
      right_idle_sprite(std::move(other.right_idle_sprite)) {}

AnimationPack &AnimationPack::operator=(AnimationPack &&other) {
    up_move_sprite = std::move(other.up_move_sprite);
    down_move_sprite = std::move(other.down_move_sprite);
    left_move_sprite = std::move(other.left_move_sprite);
    right_move_sprite = std::move(other.right_move_sprite);
    up_idle_sprite = std::move(other.up_idle_sprite);
    down_idle_sprite = std::move(other.down_idle_sprite);
    left_idle_sprite = std::move(other.left_idle_sprite);
    right_idle_sprite = std::move(other.right_idle_sprite);
    return *this;
}

AnimationPack::~AnimationPack() {}

void AnimationPack::render(Orientation orientation, MovementStatus status,
                           const SDLArea &dest) {
    switch (orientation) {
        case UP:
            if (status == IDLE)
                up_idle_sprite.render(dest);
            else if (status == MOVING)
                up_move_sprite.render(dest);
            break;
        case DOWN:
            if (status == IDLE)
                down_idle_sprite.render(dest);
            else if (status == MOVING)
                down_move_sprite.render(dest);
            break;
        case RIGHT:
            if (status == IDLE)
                right_idle_sprite.render(dest);
            else if (status == MOVING)
                right_move_sprite.render(dest);
            break;
        case LEFT:
            if (status == IDLE)
                left_idle_sprite.render(dest);
            else if (status == MOVING)
                left_move_sprite.render(dest);
            break;
    }
}