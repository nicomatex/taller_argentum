#ifndef RANDOM_EVENT_GENERATOR_H
#define RANDOM_EVENT_GENERATOR_H

#include <array>
#include <cstdlib>
#include <random>

#define N_DROP_TYPES 4

typedef enum {
    nothing,
    rand_gold,
    rand_potion,
    rand_item,
    invalid
} random_drop_t;

typedef struct range_t {
    float min_value;
    float max_value;
} range_t;

class RandomEventGenerator {
   private:
    std::array<random_drop_t, N_DROP_TYPES> events;
    std::array<range_t, N_DROP_TYPES> range_events;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> drops_dist;

    RandomEventGenerator(const char* random_events = "../ind/random_events.json");

   public:
    ~RandomEventGenerator();
    static RandomEventGenerator& get_instance();
    /**
     * @brief Devuelve un evento de forma random en base a las probabilidades
     * provistas
     * 
     * @return random_drop_t 
     */
    static random_drop_t roll();

    /* Devuelve un numero entero entre min y max */
    static uint16_t random_in(uint16_t min, uint16_t max);
    /**
     * @brief Devuelve un indice random entre 0 y tamaño del vector-1
     * 
     * @param list_size 
     * @return unsigned int 
     */
    static unsigned int rand_idx_in_vec(unsigned int vec_size);

};

#endif  // RANDOM_EVENT_GENERATOR_H