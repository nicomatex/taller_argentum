#ifndef __CAMERA_H
#define __CAMERA_H

#include "visual_component.h"

class Camera{
    private:
        /* Ancho que se va a renderizar en tiles. */
        int width_tiles;

        /* Altura que se va a renderizar en tiles. */
        int height_tiles;

        /* Coordenadas del tile donde esta centrada la camara. */
        int x_center_tile;
        int y_center_tile;

        /* Ofset del campo de vision respecto del tile central, en pixeles.
        Usado para suavizar el movimiento de la camara. */
        int x_offset_pixels; 
        int y_offset_pixels;

    public:
        Camera(const VisualComponent &follow_component);
        ~Camera();
};

#endif