#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "event.h"

/**
 * @brief Clase abstracta para el manejo de eventos.
 *
 */
class EventHandler {
   public:
    virtual ~EventHandler() {}

    /**
     * @brief Verificar si un EventHandler tiene un thread dedicado.
     *
     * La clase base no tiene un thread dedicado, pero alguna clase hija podría
     * tenerlo.
     *
     * @return false
     */
    virtual bool is_threaded() const {
        return false;
    }

    virtual void push_event(const Event& event) = 0;
};

#endif  // EVENT_HANDLER_H
