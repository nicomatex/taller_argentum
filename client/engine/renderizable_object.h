#ifndef __RENDERIZABLE_OBJECT_H
#define __RENDERIZABLE_OBJECT_H

/* Interfaz que deben implementar todos los objetos que vayan
a ser renderizados por pantalla. */
#include <mutex>

#include "SDL/sdl_animated_sprite.h"
#include "SDL/sdl_timer.h"

/**
 * @brief Struct de informacion visual.
 *
 */
typedef struct part_visual_info {
    int width;    /**< Ancho del objeto en centesimas de tile. */
    int height;   /**< Alto del objeto en centesimas de tile. */
    int offset_x; /**< Offset X respecto de la esquina del tile, en centesimas
                     de tile. */
    int offset_y; /**< Offset Y respecto de la esquina del tile, en centesimas
                     de tile. */
} visual_info_t;

/**
 * @brief Interfaz que deben implementar todos los componentes que vayan a
 * ser renderizados por la camara.
 *
 */
class RenderizableObject {
   protected:
    visual_info_t visual_info;

   public:
    /**
     * @brief Crea un objeto RenderizableObject
     *
     * @param visual_info Struct de informacion visual.
     */
    RenderizableObject(visual_info_t visual_info);
    virtual ~RenderizableObject() {}

    /**
     * @brief Renderiza el objeto en pantalla.
     *
     * @param dest Cuadro de la pantalla donde se va a renderizar.
     */
    virtual void render(SDL_Rect dest) = 0;

    /**
     * @brief Devuelve el ancho en centesimas de tile.
     *
     * @return int
     */
    int get_width() const;

    /**
     * @brief Devuelve el alto en centesimas de tile.
     *
     * @return int
     */
    int get_height() const;

    /**
     * @brief Devuelve el offset X total.
     *
     * @return int
     */
    virtual int get_x_offset() const;

    /**
     * @brief Devuelve el offset Y total.
     *
     * @return int
     */
    virtual int get_y_offset() const;

    RenderizableObject(const RenderizableObject& other);
    RenderizableObject& operator=(const RenderizableObject& other);
    /* Debe ser llamado luego de renderizar para actualizar el estado de las
    constantes visuales.*/

    /**
     * @brief Setea la informacion visual.
     * 
     * @param new_visual_info Nuevo struct de informacion visual.
     */
    void set_visual_info(visual_info_t new_visual_info);

    /**
     * @brief Actualiza el objeto.
     * 
     */
    virtual void update();
};

#endif
