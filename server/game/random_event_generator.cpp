#include "random_event_generator.h"

#include <random>

RandomEventGenerator::RandomEventGenerator()
    : events{nothing, rand_gold, rand_potion, rand_item},
      gen(rd()),
      drops_dist(0, 1) {
    std::array<float, N_DROP_TYPES> prob_events{NOTHING_PROB, GOLD_PROB,
                                                POTION_PROB, RANDOM_OBJECT};
    std::array<float, N_DROP_TYPES> norm_events;
    int sum_prob =
        std::accumulate(std::begin(prob_events), std::end(prob_events), 0);

    for (unsigned int i = 0; i < N_DROP_TYPES; i++) {
        norm_events[i] = prob_events[i] / sum_prob;
    }

    for (unsigned int i = 0; i < N_DROP_TYPES; i++) {
        if (i == 0) {
            range_events[i] = range_t{0, norm_events[i]};
        } else if (i == N_DROP_TYPES - 1) {
            range_events[i] = range_t{range_events[i - 1].max_value, 1};
        } else {
            range_events[i] =
                range_t{range_events[i - 1].max_value,
                        range_events[i - 1].max_value + norm_events[i]};
        }
    }
}

RandomEventGenerator::~RandomEventGenerator() {}

RandomEventGenerator& RandomEventGenerator::get_instance() {
    static RandomEventGenerator reg;
    return reg;
}

/**
 * @brief Devuelve true si value se encuentra entre [min_value, max_value),
 * false en caso contrario.
 * 
 * @param value 
 * @param range 
 * @return true 
 * @return false 
 */
static bool isInRange(float value, range_t& range) {
    return value >= range.min_value && value < range.max_value;
}

random_drop_t RandomEventGenerator::roll() {
    RandomEventGenerator& reg = get_instance();
    float generated = reg.drops_dist(reg.gen);
    for (unsigned int i = 0; i < N_DROP_TYPES; i++) {
        if (isInRange(generated, reg.range_events[i])) {
            return reg.events[i];
        }
    }
    return invalid;
}

uint16_t RandomEventGenerator::random_in(uint16_t min, uint16_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint16_t> distrib(min, max);
    return distrib(gen);
}
