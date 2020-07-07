#ifndef __INVENTORY_H
#define __INVENTORY_H
#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/UI/icon_grid.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "item_button_grid.h"
#include "item_qty_grid.h"

/**
 * @brief Inventario del jugador.
 * 
 */
class Inventory {
   private:
    IconGrid inventory_icons;
    SDL_Rect inventory_area;
    ItemQtyGrid item_qty_grid;
    ItemButtonGrid item_button_grid;

   public:
    /**
     * @brief Constructor del objeto inventory.
     *
     * @param inventory_area Area donde se va a renderizar el inventario.
     * @param viewport Viewport donde se encuentra el inventario.
     * @param rows Filas del inventario.
     * @param cols Columnas del inventario.
     * @param numbers_font Fuente a utilizar para los numeros de cantidades.
     * @param renderer Renderer con el que se va a renderizar el inventario.
     * @param socket_manager Socket Manager del juego.
     */
    Inventory(SDL_Rect inventory_area, SDL_Rect viewport, int rows, int cols,
              TTF_Font* numbers_font, SDL_Renderer* renderer,
              SocketManager& socket_manager);
    ~Inventory();

    /**
     * @brief Renderiza el inventario.
     *
     */
    void render();

    /**
     * @brief Setea el item en un slot.
     *
     * @param slot Slot a modificar
     * @param icon Icono a ubicar en el slot
     * @param quantity Cantidad a mostrar en el slot.
     */
    void set_item(int slot, SDLTexture* icon, int quantity);

    /**
     * @brief Maneja eventos (clicks) en el inventario.
     *
     * @param e Evento.
     */
    void handle_event(SDL_Event& e);

    /**
     * @brief Devuelve el ultimo slot del inventario que fue clickeado.
     *
     * @return int
     */
    int get_last_clicked_slot();
};

#endif