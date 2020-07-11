#ifndef __GAME_STATE_MONITOR_H
#define __GAME_STATE_MONITOR_H

#include <condition_variable>
#include <mutex>

/**
 * @brief Enum de estados de ejecucion del cliente.
 *
 */
typedef enum {
    LOGGING,
    WAITING_FOR_INITIALIZATION,
    READY_TO_RUN,
    RUNNING,
    SWITCHING_MAPS,
    EXITING,
    CREATING_CHARACTER
} game_state_t;

typedef enum { FIRST_LOGIN, NAME_NOT_FOUND, NAME_ALREADY_CONECTED } login_state_t;

typedef enum { FIRST_TRY, NAME_TAKEN } char_creation_state_t;

/**
 * @brief Monitor mediante el cual se sincroniza el flujo entre vistas.
 *
 */
class GameStateMonitor {
   private:
    std::mutex m;
    bool connected;
    game_state_t game_state;
    login_state_t login_state;
    char_creation_state_t char_creation_state;
    std::condition_variable cv;

   public:
    GameStateMonitor();
    ~GameStateMonitor();

    /**
     * @brief Indica si el cliente esta conectado.
     *
     * @return true Si esta conectado
     * @return false Si no esta conectado.
     */
    bool is_connected();

    /**
     * @brief Setea el nuevo estado de conexion.
     *
     * @param new_connection_status Nuevo estado de conexion.
     */
    void set_connected_status(bool new_connection_status);

    /**
     * @brief Setea el nuevo estado del juego.
     *
     * @param new_game_state Nuevo estado del juego.
     */
    void set_game_state(game_state_t new_game_state);

    /**
     * @brief Devuelve el estado del juego.
     *
     * @return game_state_t
     */
    game_state_t get_game_state();

    /**
     * @brief Setea el nuevo estado del login.
     * 
     * @param new_login_state Nuevo estado del login.
     */
    void set_login_state(login_state_t new_login_state);

    /**
     * @brief Devuelve el estado de login.
     * 
     * @return login_state_t 
     */
    login_state_t get_login_state();

    /**
     * @brief Setea el nuevo estado de creacion de personaje.
     * 
     * @param new_char_creation_state Nuevo estado de creacion de personaje.
     */
    void set_char_creation_state(char_creation_state_t new_char_creation_state);

    /**
     * @brief Devuelve el estado de creacion de personaje.
     * 
     * @return char_creation_state_t 
     */
    char_creation_state_t get_char_creation_state();

    /* Duerme el thread llamante hasta que el estado del juego
    sea el esperado. */

    /**
     * @brief Duerme el thread llamante hasta que el estado del juego
     * sea el esperado.
     *
     * @param expected_game_state Estado de juego esperado.
     */
    void wait_for_game_state(game_state_t expected_game_state);

    /* Duerme el thread llamante hasta que haya algun
    cambio de estado. */
    /**
     * @brief Duerme el thread llamante hasta que haya un cambio de estado.
     *
     */
    void wait_for_next_game_state();

    /**
     * @brief Setea el estado como desconectado, y el estado de juego como
     * EXITING.
     *
     */
    void quit();
};

#endif