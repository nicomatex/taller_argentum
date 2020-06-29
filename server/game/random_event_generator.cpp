#include "random_event_generator.h"

RandomEventGenerator::RandomEventGenerator() : events{nothing, gold,
                                              		  potion, random_object},
											   gen(rd()),
											   dist(0,1) {
	std::array<float, N_EVENTS> prob_events{NOTHING_PROB, GOLD_PROB,
                                            POTION_PROB, RANDOM_OBJECT};
	std::array<float, N_EVENTS> norm_events;
	int sum_prob = std::accumulate(std::begin(prob_events),
                                   std::end(prob_events), 0);

	for (unsigned int i = 0; i < N_EVENTS; i++) {
        norm_events[i] = prob_events[i]/sum_prob;
    }

	for (unsigned int i = 0; i < N_EVENTS; i++) {
        if (i == 0) {
            range_events[i] = range_t{0, norm_events[i]};
        } else if (i == N_EVENTS - 1) {
            range_events[i] = range_t{range_events[i-1].max_value, 1};
        } else {
            range_events[i] = range_t{range_events[i-1].max_value,
                                      range_events[i-1].max_value + 
                                      norm_events[i]};
        }   
    }
}

RandomEventGenerator::~RandomEventGenerator() {}

/*
	Devuelve true si value se encuentra entre [min_value, max_value),
	false en caso contrario.
*/
static bool isInRange(float value, range_t& range) {
    return value >= range.min_value && value < range.max_value;
}

random_event_t RandomEventGenerator::roll() {
	float generated = dist(gen);
    for (unsigned int i = 0; i < N_EVENTS; i++) {
        if (isInRange(generated, range_events[i])) {
            return events[i];
        }
    }
    return invalid;
}

