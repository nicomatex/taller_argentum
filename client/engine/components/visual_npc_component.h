#ifndef __VISUAL_NPC_COMPONENT_H
#define __VISUAL_NPC_COMPONENT_H

#include "../../../include/nlohmann/json.hpp"
#include "../../../include/types.h"
#include "../ECS/component.h"
#include "../actor.h"
#include "../camera.h"
#include "../in_game_text.h"

/**
 * @brief Componente visual de los NPCs.
 *
 */
class VisualNPCComponent : public Component {
   private:
    int speed;  // En tiles/segundo.
    /* Indica si ya se recibio el primer mensaje de actualizacion de posicion.*/
    bool initialized;
    Actor body;
    int transition_offset_x;
    int transition_offset_y;
    InGameText render_name;
    InGameText render_damage;
    bool recently_damaged;
    SDLTimer damage_render_timer;
    SDLTimer transition_timer;
    /* Actualiza el offset de renderizacion. */
    void _update_offset();
    void _update_animation(int delta_x, int delta_y);
    int current_x;
    int current_y;

    std::recursive_mutex m;

   public:
    /**
     * @brief Crea un objeto VisualNPCComponent
     *
     * @param body_id id del cuerpo del NPC.
     * @param speed Velocidad de movimiento del npc en tiles/segundo.
     */
    VisualNPCComponent(int body_id, int speed, const std::string& name);
    ~VisualNPCComponent();

    /**
     * @brief Setea la orientacion del NPC.
     *
     * @param new_orientation Nueva orientacion del NPC.
     */
    void set_orientation(direction_t new_orientation);
    void init() override;
    void update() override;

    /**
     * @brief Dibuja el npc.
     *
     * @param camera Camara con la cual se desea renderizar el NPC.
     */
    void draw(Camera& camera);

    /**
     * @brief Actualiza el NPC segun la informacion recibida en una
     * actualizacion proveniente del servidor.
     *
     * @param update_info json con la informacion de la actualizacion.
     */
    void server_update(nlohmann::json update_info);

    /**
     * @brief Indica si el NPC se esta moviendo.
     *
     * @return true si el NPC se esta moviendo.
     * @return false si el NPC no se esta moviendo.
     */
    bool is_moving();

    /**
     * @brief Indica que se debe renderizar el danio recibido.
     * 
     * @param damage Danio recibido.
     */
    void display_damage(int damage);
};

#endif