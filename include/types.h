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

typedef enum {
    TYPE_INVALID = 0,
    TYPE_WEAPON = 1,
    TYPE_ARMOR = 2,
    TYPE_POTION = 3,
    TYPE_GOLD = 4
} item_type_t;

typedef uint32_t ClientId;

typedef uint32_t EntityId;

typedef int32_t MapId;

typedef int32_t ItemId;

typedef uint8_t SlotId;

#endif  // TYPES_H
