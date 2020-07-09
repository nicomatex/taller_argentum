#ifndef __ITEM_BUTTON_H
#define __ITEM_BUTTON_H

#include "../../../include/network/socket_manager.h"
#include "../../engine/SDL/sdl_timer.h"
#include "../../engine/UI/button.h"

/**
 * @brief Boton clickeable para cada item del inventario.
 *
 */
class ItemButton : public Button {
   private:
    SlotId slot_number;
    int& last_clicked_slot;
    SocketManager& socket_manager;
    Event (*left_click_event)(SlotId);
    Event (*right_click_event)(SlotId);
    SDLTimer double_click_timer;

   public:
    /**
     * @brief Crea un objeto Item Button
     *
     * @param button_area Area del boton.
     * @param viewport Viewport donde esta el boton.
     * @param renderer Renderer con el que se va a renderizar el boton.
     * @param slot_number Numero de slot que representa el boton.
     * @param last_clicked_slot Referencia para trackear el ultimo slot
     * clickeado.
     * @param socket_manager Socket manager del juego.
     */
    ItemButton(SDL_Rect button_area, SDL_Rect viewport, SDL_Renderer* renderer,
               SlotId slot_number, int& last_clicked_slot,
               SocketManager& socket_manager, Event (*left_click_event)(SlotId),
               Event (*right_click_event)(SlotId));

    /**
     * @brief Un click setea el ultimo slot clickeado. Doble click envia un
     * evento de usar sobre el slot.
     *
     */
    void on_click() override;

    /**
     * @brief Envia un evento de tirar item al piso sobre el slot.
     *
     */
    void on_right_click() override;
};

#endif