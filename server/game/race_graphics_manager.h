#ifndef RACE_GRAPHICS_MANAGER_H
#define RACE_GRAPHICS_MANAGER_H

#include <unordered_map>

#include "../../include/types.h"

class RaceGraphicsManager {
   private:
    static std::unordered_map<race_type_t, uint32_t> race_heads_map;
    static std::unordered_map<race_type_t, uint32_t> race_bodies_map;

   public:
    RaceGraphicsManager();
    ~RaceGraphicsManager();
    /**
     * @brief Se inicializan los diccionarios de los id's de las cabezas y cuerpos,
     * asociados a las distintas razas.
     * Lanza MyException en caso de que no exista el archivo, o en caso de
     * error.
     * 
     * @param races_file 
     */
    static void init(const char *races_file);
    /**
     * @brief Devuelve el id de sprite de la cabeza asociada a la raza
     * Lanza MyException en caso de no existir la raza.
     * 
     * @param race_type 
     * @return uint32_t 
     */
    static uint32_t get_race_head(race_type_t race_type);
    /**
     * @brief Devuelve el id de sprite del cuerpo asociado a la raza
     * Lanza MyException en caso de no existir la raza.
     * 
     * @param race_type 
     * @return uint32_t 
     */
    static uint32_t get_race_body(race_type_t race_type);
};

#endif  // RACE_GRAPHICS_MANAGER_H