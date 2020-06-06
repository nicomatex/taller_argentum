#ifndef __SDL_AREA_H
#define __SDL_AREA_H

class SDLArea {
   private:
    int x, y;
    int width, height;

   public:
    SDLArea(int x, int y, int width, int height);
    SDLArea();
    ~SDLArea();

    /* Devuelve la posicion X del area. */
    int getX() const;

    /* Devuelve la posicion Y del area. */
    int getY() const;

    /* Devuelve el ancho del area. */
    int getWidth() const;

    /* Devuelve el alto del area. */
    int getHeight() const;

    /* Establece la posicion del area como la pasada por parametro. */
    void set_new_pos(const int new_x, const int new_y);

    void set_new_size(const int new_width, const int new_height);
};

#endif