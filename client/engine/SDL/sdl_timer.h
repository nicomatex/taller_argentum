#ifndef __TIMER_H
#define __TIMER_H
#include <cstdint>

/**
 * @brief Timer basado en la cuenta de SDL.
 * 
 */
class SDLTimer {
   private:
    bool _is_started;
    bool _is_paused;

    uint32_t start_ticks;
    uint32_t pause_ticks;

   public:
    /**
     * @brief Crea un objeto SDLTimer
     * @details Permite medir el paso del tiempo en la ejecucion del programa.
     */
    SDLTimer();
    ~SDLTimer();

    /**
     * @brief Crea un objeto SDLTimer por copia.
     *
     * @param other Otro timer.
     */
    SDLTimer(const SDLTimer &other);
    SDLTimer &operator=(const SDLTimer &other);

    /* Constructor por movimiento. */
    SDLTimer(SDLTimer &&other);
    SDLTimer &operator=(SDLTimer &&other);

    /**
     * @brief Inicia la cuenta del timer.
     *
     */
    void start();

    /**
     * @brief Detiene la cuenta del timer.
     *
     */
    void stop();

    /**
     * @brief Pausa la cuenta del timer.
     *
     */
    void pause();

    /**
     * @brief Despausa la cuenta del timer.
     *
     */
    void unpause();

    /**
     * @brief Devuelve el tiempo transcurrido desde que se inicio el timer.
     *
     * @return uint32_t
     */
    uint32_t get_ticks() const;

    /**
     * @brief Indica si el timer esta iniciado.
     * 
     * @return true 
     * @return false 
     */
    bool is_started() const;

    /**
     * @brief Indica si el timer esta pausado.
     * 
     * @return true 
     * @return false 
     */
    bool is_paused() const;
};

#endif