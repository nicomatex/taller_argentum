#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

#ifndef MOVEMENT_ACTION_T
#define MOVEMENT_ACTION_T
enum mov_action_t { START, STOP };
#endif

#ifndef DIRECTION_T
#define DIRECTION_T
enum direction_t { UP, DOWN, LEFT, RIGHT };
#endif

typedef uint32_t ClientId;

typedef uint32_t EntityId;

typedef uint32_t MapId;

#endif  // TYPES_H
