#include "sdl_animated_sprite.h"

#include "sdl_error.h"

SDLSprite::SDLSprite(SDLTexture& texture, int nframes, int fps, int base_x,
                     int base_y, int w, int h)
    : texture(texture),
      nframes(nframes),
      frame_width(w),
      frame_height(h),
      current_frame(0),
      base_x(base_x),
      base_y(base_y),
      time_between_frames(1000 / fps) {
    timer.start();
}

SDLSprite::SDLSprite(SDLSprite&& other) : texture(other.texture) {
    this->nframes = std::move(other.nframes);
    this->frame_width = std::move(other.frame_width);
    this->frame_height = std::move(other.frame_height);
    this->current_frame = std::move(other.current_frame);
    this->base_x = std::move(other.base_x);
    this->base_y = std::move(other.base_y);
    this->time_between_frames = std::move(other.time_between_frames);
    this->timer = std::move(other.timer);
}

SDLSprite& SDLSprite::operator=(SDLSprite &&other){
    texture = std::move(other.texture);
    this->nframes = std::move(other.nframes);
    this->frame_width = std::move(other.frame_width);
    this->frame_height = std::move(other.frame_height);
    this->current_frame = std::move(other.current_frame);
    this->base_x = std::move(other.base_x);
    this->base_y = std::move(other.base_y);
    this->time_between_frames = std::move(other.time_between_frames);
    this->timer = std::move(other.timer);
    return *this;
}

SDLSprite::~SDLSprite(){}

void SDLSprite::render(const SDLArea& dest) {
    /* Actualizacion del cuadro de la animacion. */
    if (timer.get_ticks() > time_between_frames) {
        current_frame = (current_frame + 1) % nframes;
        timer.start();
    }

    SDLArea src(base_x + (current_frame * frame_width), base_y, frame_width,
                frame_height);
    SDL_Rect sdlDest = {dest.getX(), dest.getY(), dest.getWidth(),
                        dest.getHeight()};
    texture.render(src, dest);
}