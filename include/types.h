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

typedef struct steps {
    int x;
    int y;
} steps_t;

typedef uint32_t ClientId;

typedef uint32_t EntityId;

typedef int32_t MapId;

typedef int32_t ItemId;

#endif  // TYPES_H
