#ifndef RANDOM_EVENT_GENERATOR_H
#define RANDOM_EVENT_GENERATOR_H

#include <array>
#include <cstdlib>
#include <random>

#define N_EVENTS 4

#define NOTHING_PROB 80
#define GOLD_PROB 8
#define POTION_PROB 1
#define RANDOM_OBJECT 11

typedef enum {
    nothing,
    rand_gold,
    rand_potion,
    random_object,
    invalid
} random_event_t;

typedef struct range_t {
    float min_value;
    float max_value;
} range_t;

class RandomEventGenerator {
   private:
    std::array<random_event_t, N_EVENTS> events;
    std::array<range_t, N_EVENTS> range_events;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;

   public:
    RandomEventGenerator();
    ~RandomEventGenerator();
    random_event_t roll();
    /*
        Devuelve un numero entero entre min y max
    */
    static uint16_t random_in(uint16_t min, uint16_t max);
};

#endif  // RANDOM_EVENT_GENERATOR_H