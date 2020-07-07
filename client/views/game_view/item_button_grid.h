#ifndef __ITEM_BUTTON_GRID_H
#define __ITEM_BUTTON_GRID_H

#include <vector>

#include "SDL2/SDL.h"
#include "item_button.h"

/**
 * @brief Wrapper para todos los botones del inventario.
 * 
 */
class ItemButtonGrid {
   private:
    std::vector<ItemButton> buttons;
    int last_clicked_slot;

   public:
    /**
     * @brief Crea un objeto Item Button Grid
     * 
     * @param inventory_area Area del inventario.
     * @param viewport Viewport donde se encuentra el inventario.
     * @param renderer Renderer con el que se van a renderizar los botones.
     * @param rows Filas del inventario.
     * @param cols Columnas del inventario.
     * @param socket_manager Socket manager del juego.
     */
    ItemButtonGrid(SDL_Rect inventory_area, SDL_Rect viewport,
                   SDL_Renderer* renderer, int rows, int cols,
                   SocketManager& socket_manager);
    ~ItemButtonGrid();

    /**
     * @brief Maneja los clicks en el inventario.
     * 
     * @param e Evento de SDL.
     */
    void handle_event(SDL_Event& e);

    /**
     * @brief Devuelve el ultimo slot clickeado.
     * 
     * @return int 
     */
    int get_last_clicked_slot();
};

#endif