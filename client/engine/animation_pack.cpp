#include "animation_pack.h"

#include <iostream>
AnimationPack::AnimationPack(
    SDLSprite &up_move_sprite, SDLSprite &down_move_sprite,
    SDLSprite &left_move_sprite, SDLSprite &right_move_sprite,
    SDLSprite &up_idle_sprite, SDLSprite &down_idle_sprite,
    SDLSprite &left_idle_sprite, SDLSprite &right_idle_sprite)
    : up_move_sprite(up_move_sprite),
      down_move_sprite(down_move_sprite),
      left_move_sprite(left_move_sprite),
      right_move_sprite(right_move_sprite),
      up_idle_sprite(up_idle_sprite),
      down_idle_sprite(down_idle_sprite),
      left_idle_sprite(left_idle_sprite),
      right_idle_sprite(right_idle_sprite) {}

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

void AnimationPack::render(direction_t direction, movement_status_t status,
                           SDL_Rect dest) {
    switch (direction) {
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

AnimationPack::AnimationPack(const AnimationPack &other)
    : up_move_sprite(other.up_move_sprite),
      down_move_sprite(other.down_move_sprite),
      left_move_sprite(other.left_move_sprite),
      right_move_sprite(other.right_move_sprite),
      up_idle_sprite(other.up_idle_sprite),
      down_idle_sprite(other.down_idle_sprite),
      left_idle_sprite(other.left_idle_sprite),
      right_idle_sprite(other.right_idle_sprite) {}

AnimationPack &AnimationPack::operator=(const AnimationPack &other) {
    up_move_sprite = other.up_move_sprite;
    down_move_sprite = other.down_move_sprite;
    left_move_sprite = other.left_move_sprite;
    right_move_sprite = other.right_move_sprite;
    up_idle_sprite = other.up_idle_sprite;
    down_idle_sprite = other.down_idle_sprite;
    left_idle_sprite = other.left_idle_sprite;
    right_idle_sprite = other.right_idle_sprite;
    return *this;
}

int AnimationPack::get_frame_width(direction_t direction) {
    int width = 0;
    switch (direction) {
        case UP:
            width = up_idle_sprite.get_frame_width();
            break;
        case DOWN:
            width = down_idle_sprite.get_frame_width();
            break;
        case RIGHT:
            width = right_idle_sprite.get_frame_width();
            break;
        case LEFT:
            width =  left_idle_sprite.get_frame_width();
            break;
    }
    return width;
}
int AnimationPack::get_frame_height(direction_t direction) {
    int height = 0;
    switch (direction) {
        case UP:
            height = up_idle_sprite.get_frame_height();
            break;
        case DOWN:
            height = down_idle_sprite.get_frame_height();
            break;
        case RIGHT:
            height = right_idle_sprite.get_frame_height();
            break;
        case LEFT:
            height = left_idle_sprite.get_frame_height();
            break;
    }
    return height;
}