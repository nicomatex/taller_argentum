#ifndef __CAMERA_H
#define __CAMERA_H

#include <vector>

#include "SDL/sdl_timer.h"
#include "components/position_component.h"
#include "decoration.h"
#include "renderizable_object.h"

typedef struct position {
    int x;
    int y;
} position_t;

/**
 * @brief Camara, utilizada para renderizar el mapa y las entidades.
 *
 */
class Camera {
   private:
    PositionComponent &follow_component;
    /* Coordenadas del tile donde esta centrada la camara. */
    int x_center_tile;
    int y_center_tile;
    int map_size; /* Lado del mapa, en tiles (los mapas son cuadrados). */

    int tile_size; /* Lado de cada tile, en pixeles.*/
    /* Ancho que se va a renderizar en tiles. */
    int width_tiles;

    /* Altura que se va a renderizar en tiles. */
    int height_tiles;

    int speed;  // En tiles/segundo.
    SDL_Rect viewport;

    int camera_offset_x;
    int camera_offset_y;

    SDLTimer movement_timer;



    /* Devuelve true si un componente visual esta dentro del campo
    de vision de la camara.*/
    bool _is_within_visual_range(RenderizableObject *component);

    /* Devuelve el area fisica donde deberia ser dibujado el componente.*/
    SDL_Rect _get_render_area(RenderizableObject *component, int x, int y,
                              int x_tmp_offset, int y_tmp_offset);
    SDL_Rect _get_render_area(Decoration &decoration);

    void _update_offset();

   public:
    /**
     * @brief Crea un objeto Camera
     *
     * @param follow_component Componente de posicion que la camara va a seguir.
     * @param viewport Viewport asociado a la camara. Utilizado para detectar el
     * tile clickeado.
     * @param map_size Tamanio del mapa que se esta mostrando en este momento.
     * @param tile_size Lado en pixeles de cada tile.
     * @param viewport_width Ancho del renderer, en tiles.
     * @param viewport_height Alto del renderer, en tiles.
     * @param speed Velocidad de la camara, en tiles/segundo.
     */
    Camera(PositionComponent &follow_component, SDL_Rect viewport, int map_size,
           int tile_size, int speed);
    ~Camera();

    /**
     * @brief Actualiza la posicion de la camara segun el objeto que esta
     * siguiendo.
     *
     */
    void update();

    /**
     * @brief Renderiza un objeto renderizable.
     *
     * @param component Objeto a renderizar.
     * @param x Coordenada X (en tiles) en la cual se reenderizara el objeto.
     * @param y Coordenada Y (en tiles) en la cual se reenderizara el objeto.
     * @param x_tmp_offset Offset en centesimas de tile temporal. Utilizado para
     * animaciones.
     * @param y_tmp_offset Offset en centesimas de tile temporal. Utilizado para
     * animaciones.
     */
    void draw(RenderizableObject *component, int x, int y, int x_tmp_offset,
              int y_tmp_offset);

    /**
     * @brief Renderiza todas las entidades que contengan una componente visual.
     *
     */
    void draw_all();

    /**
     * @brief Renderiza un conjunto de capas del mapa.
     *
     * @param layers Vector de capas del mapa.
     */
    void render_map_layers(std::vector<std::vector<Decoration>> &layers);

    /**
     * @brief Indica cual fue el tile clickeado.
     *
     * @param x Coordenada X (en pixeles) donde ocurrio el click.
     * @param y Coordenada Y (en pixeles) donde ocurrio el click.
     * @return position_t
     */
    position_t tile_at(int x, int y);
};

#endif
