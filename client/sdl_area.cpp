#include "sdl_area.h"

SDLArea::SDLArea(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

SDLArea::~SDLArea(){}

int SDLArea::getHeight() const{ return height; }

int SDLArea::getWidth() const { return width; }

int SDLArea::getX() const{ return x; }
int SDLArea::getY() const{ return y; }

void SDLArea::set_new_pos(const int new_x, const int new_y){
    x = new_x;
    y = new_y;
}

void SDLArea::set_new_size(const int new_width,const int new_height){
    width = new_width;
    height = new_height;
}