#include "sdl_animated_sprite.h"

#include <iostream>

#include "sdl_error.h"
using json = nlohmann::json;

SDLSprite::SDLSprite(SDLTexture& texture, int nframes, int fps, int base_x,
                     int base_y, int w, int h)
    : texture(texture),
      nframes(nframes),
      frame_width(w),
      frame_height(h),
      current_frame(0),
      base_x(base_x),
      base_y(base_y),
      time_between_frames(1000 / fps),
      done(false) {
    timer.start();
}

SDLSprite::SDLSprite(SDLTexture& texture, json sprite_info)
    : SDLSprite(texture, int(sprite_info["frames"]), int(sprite_info["fps"]),
                int(sprite_info["base x"]), int(sprite_info["base y"]),
                int(sprite_info["frame width"]),
                int(sprite_info["frame height"])) {}

SDLSprite::SDLSprite(const SDLSprite& other) : texture(other.texture) {
    this->nframes = other.nframes;
    this->frame_width = other.frame_width;
    this->frame_height = other.frame_height;
    this->current_frame = other.current_frame;
    this->base_x = other.base_x;
    this->base_y = other.base_y;
    this->time_between_frames = other.time_between_frames;
    this->timer = other.timer;
}

SDLSprite& SDLSprite::operator=(const SDLSprite& other) {
    this->texture = other.texture;
    this->nframes = other.nframes;
    this->frame_width = other.frame_width;
    this->frame_height = other.frame_height;
    this->current_frame = other.current_frame;
    this->base_x = other.base_x;
    this->base_y = other.base_y;
    this->time_between_frames = other.time_between_frames;
    this->timer = other.timer;
    return *this;
}

SDLSprite::SDLSprite(SDLSprite&& other) : texture(other.texture), done(false) {
    this->nframes = std::move(other.nframes);
    this->frame_width = std::move(other.frame_width);
    this->frame_height = std::move(other.frame_height);
    this->current_frame = std::move(other.current_frame);
    this->base_x = std::move(other.base_x);
    this->base_y = std::move(other.base_y);
    this->time_between_frames = std::move(other.time_between_frames);
    this->timer = std::move(other.timer);
}

SDLSprite& SDLSprite::operator=(SDLSprite&& other) {
    texture = std::move(other.texture);
    this->nframes = std::move(other.nframes);
    this->frame_width = std::move(other.frame_width);
    this->frame_height = std::move(other.frame_height);
    this->current_frame = std::move(other.current_frame);
    this->base_x = std::move(other.base_x);
    this->base_y = std::move(other.base_y);
    this->time_between_frames = std::move(other.time_between_frames);
    this->timer = std::move(other.timer);
    this->done = false;
    return *this;
}

SDLSprite::~SDLSprite() {}

void SDLSprite::render(SDL_Rect dest) {
    /* Actualizacion del cuadro de la animacion. */
    if (timer.get_ticks() > time_between_frames) {
        current_frame = (current_frame + 1) % nframes;
        timer.start();
        if (current_frame == 0)
            done = true;  // Ya se reprodujo la animacion completa una vez.
    }
    int frames_per_row = texture.get().get_width() / frame_width;

    int x_start_render =
        base_x + ((current_frame % frames_per_row) * frame_width);

    int y_start_render =
        base_y + (current_frame / frames_per_row) * frame_height;

    SDL_Rect src = {x_start_render, y_start_render, frame_width, frame_height};

    texture.get().render(src, dest);
}

int SDLSprite::get_frame_width() { return frame_width; }
int SDLSprite::get_frame_height() { return frame_height; }

bool SDLSprite::is_done() { return done; }