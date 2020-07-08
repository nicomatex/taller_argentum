#ifndef __EQUIPMENT_H
#define __EQUIPMENT_H

#include "../../engine/SDL/sdl_texture.h"
#include "../../engine/UI/icon_grid.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "item_button_grid.h"

class Equipment {
   private:
    IconGrid equipment_icons;
    SDL_Rect equipment_area;
    ItemButtonGrid item_button_grid;

   public:
    Equipment(SDL_Rect equipment_area, SDL_Rect viewport,
              SDL_Renderer* renderer, SocketManager& socket_manager);
    ~Equipment();

    /**
     * @brief Renderiza el equipamiento.
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
    void set_item(int slot, SDLTexture* icon);

    /**
     * @brief Maneja eventos (clicks) en el equipamiento.
     *
     * @param e Evento.
     */
    void handle_event(SDL_Event& e);

    /**
     * @brief Devuelve el ultimo slot del equipamiento que fue clickeado.
     *
     * @return int
     */
    int get_last_clicked_slot();
};

#endif  // __EQUIPMENT_H
