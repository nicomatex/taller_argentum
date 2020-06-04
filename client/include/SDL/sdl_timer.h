#ifndef __TIMER_H
#define __TIMER_H
#include <cstdint>

class SDLTimer{
    private:
        bool _is_started;
        bool _is_paused;

        uint32_t start_ticks;
        uint32_t pause_ticks;
    public:
        /* Crea un timer que permite medir paso del tiempo en la ejecucion
        del programa. */
        SDLTimer();
        ~SDLTimer();

        /* Constructor por copia. */
        SDLTimer(const SDLTimer &other);
        SDLTimer& operator=(const SDLTimer &other);

        /* Constructor por movimiento. */
        SDLTimer(SDLTimer &&other);
        SDLTimer& operator=(SDLTimer &&other);

        /* Inicia la cuenta del timer. */
        void start();

        /* Detiene la cuenta del timer. */
        void stop();

        /* Pausa la cuenta del timer. */
        void pause();

        /* Despausa la cuenta del timer.*/
        void unpause();

        /* Obtiene el tiempo pasado desde que se inicio el timer. */
        uint32_t get_ticks() const;

        /* Devuelve true si el timer esta iniciado. */
        bool is_started() const;

        /* Devuelve true si el timer esta pausado. */
        bool is_paused() const;
};

#endif