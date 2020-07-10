#ifndef __SDL_TEXTURE_H
#define __SDL_TEXTURE_H
#include <cstdint>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/**
 * @brief Objeto de textura de SDL.
 * 
 */
class SDLTexture {
   protected:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;

   public:
    /* Usado para crear texturas sin color key. */

    /**
     * @brief Crea un objeto SDLTexture vacio.
     *
     * @param renderer Renderer al cual se asocia la textura.
     */
    SDLTexture(SDL_Renderer* renderer);

    SDLTexture(const std::string& filename, SDL_Renderer* renderer);

    /**
     * @brief Crea un objeto SDLTexture.
     * @details Toma como transparencia el color key indicado en los parametros
     * r,g,b.
     *
     * @param filename Nombre del archivo a partir del cual se debe generar la
     * textura.
     * @param renderer Renderer al cual se asocia la textura.
     * @param r Rojo del color key.
     * @param g Verde del color key.
     * @param b Azul del color key.
     */
    SDLTexture(const std::string& filename, SDL_Renderer* renderer, uint8_t r,
               uint8_t g, uint8_t b);

    /* No se permite construccion por copia. */
    SDLTexture(const SDLTexture& other) = delete;
    SDLTexture& operator=(const SDLTexture& other) = delete;

    /* Constructor por movimiento. */
    SDLTexture(SDLTexture&& other);
    SDLTexture& operator=(SDLTexture&& other);

    virtual ~SDLTexture();

    /**
     * @brief Renderiza la textura
     *
     * @param src Cuadro de origen dentro de la textura (si no se desea
     * renderizar la totalidad de la misma).
     * @param dest Cuadro de destino en pantalla.
     */
    void render(SDL_Rect src, SDL_Rect dest) const;

    /**
     * @brief Renderiza la textura
     *
     * @param dest Cuadro de destino en pantalla.
     */
    void render(SDL_Rect dest) const;

    int get_width() const;
    int get_height() const;

    void set_color_mod(uint8_t r, uint8_t g, uint8_t b);

    void reset_color_mod();
};

#endif