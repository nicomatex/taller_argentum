#ifndef __VISUAL_CHARACTER_COMPONENT
#define __VISUAL_CHARACTER_COMPONENT
#include <unordered_map>

#include "../../../include/types.h"
#include "../ECS/component.h"
#include "../actor.h"
#include "../camera.h"
#include "../in_game_text.h"
#include "../in_game_bar.h"
#include "../visual_effect.h"


typedef std::unordered_map<std::string, Actor> Parts;
typedef std::unordered_map<std::string, int> PartIds;

/**
 * @brief Componente visual de los personajes.
 * 
 */
class VisualCharacterComponent : public Component {
   private:
    int speed;  // En tiles/segundo.
    bool initialized;
    int transition_offset_x;
    int transition_offset_y;
    Parts parts;
    PartIds part_ids;
    InGameText render_name;
    InGameText render_damage;
    InGameBar health_bar;
    VisualEffect meditation_effect;
    bool recently_damaged;
    bool is_meditating;
    SDLTimer damage_render_timer;
    SDLTimer transition_timer;
    /* Actualiza el offset de renderizacion. */
    void _update_offset();
    void _update_animation(int delta_x, int delta_y);
    int current_x;
    int current_y;

    /* Indica si ya se recibio el primer mensaje de actualizacion de posicion.*/
    std::recursive_mutex m;

    void _draw_if_present(Camera &camera, const std::string &part_name);

   public:
    /**
     * @brief Crea un objeto VisualCharacterComponent
     *
     * @details Si alguno de los id es cero, no se renderizara la parte con id
     * 0.
     *
     * @param head_id id de la cabeza.
     * @param body_id id del cuerpo.
     * @param weapon_id id del arma.
     * @param shield_id id del escudo.
     * @param helmet_id id del casco.
     * @param armor_id id de la armadura.
     * @param speed velocidad de movimiento del jugador.
     */
    VisualCharacterComponent(int head_id, int body_id, int weapon_id,
                             int shield_id, int helmet_id, int armor_id,
                             int speed, const std::string& name);
    ~VisualCharacterComponent();

    /**
     * @brief Devuelve una de las partes visuales.
     *
     * @param type Tipo de la parte que se desea obtener.
     * @return Actor&
     */
    Actor &get_part(const std::string &type);

    /**
     * @brief Actualiza el jugador segun la informacion de actualizacion
     * obtenida del servidor.
     *
     * @param update_info json con la informacion de actualizacion
     * correspondiente.
     */
    void server_update(nlohmann::json update_info);

    /**
     * @brief Cambia una parte.
     *
     * @param type Tipo de la parte que se desea cambiar.
     * @param texture_family Familia de texturas de la parte que se desea
     * cambiar.
     * @param new_part_id id de la nueva parte.
     * @param visual_info struct de informacion visual.
     */
    void set_part(const std::string &type, const std::string &texture_family,
                  int new_part_id, visual_info_t visual_info);

    /**
     * @brief Setea la nueva orientacion del personaje.
     *
     * @param new_orientation Nueva orientacion.
     */
    void set_orientation(direction_t new_orientation);
    void init() override;
    void update() override;

    /**
     * @brief Dibuja el personaje.
     *
     * @param camera Camara con la que se desea renderizar el personaje.
     */
    void draw(Camera &camera);

    /**
     * @brief Devuelve el id asociado a una parte.
     *
     * @param part_name Tipo de la parte para la cual se desea obtener el id.
     * @return int
     */
    int get_part_id(const std::string &part_name);

    /**
     * @brief Indica si el personaje se esta moviendo.
     * 
     * @return true si se esta moviendo.
     * @return false si no se esta moviendo.
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