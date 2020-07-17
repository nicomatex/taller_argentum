#ifndef __VISUAL_CONFIG_H
#define __VISUAL_CONFIG_H

/* Tamanios en centesimas de tile */

/* Configuraciones en formato {WIDTH, HEIGHT, X_OFFSET, Y_OFFSET}*/
#define HEAD_CONFIG {60,60,20,-186}
#define BODY_CONFIG {100,180,0,-40}
#define WEAPON_CONFIG {100,180,0,-40}
#define SHIELD_CONFIG {100,180,0,-40}

#define FLOOR_TILE_CONFIG {100,100,0,0}

#define SPELL_CONFIG {200,200,-50,0}

/* Meditacion */
#define MEDITATION_ID 1
#define MEDITATION_CONFIG {200, 400, -50, 0}


#define NAME_COLOR {0,0,255,0}
#define MONSTER_NAME_COLOR {255,114,0,0}
#define NAME_FONT_ID 1
#define NAME_INFO {0,60,0,0}
#define HEALTH_BAR_INFO {120, 20, -10, 10}

#define DAMAGE_COLOR {255,0,0,0}
#define DAMAGE_FONT_ID 1
#define DAMAGE_INFO {0,60,0,-100}
#define DAMAGE_TEXT_DURATION 1100 //ms

#define PATTERN_TILE_SIZE 32 //Los tiles patron tienen 32px. 
#define NPC_SIZE_FACTOR 1.3 //Para hacer los npcs mas grandes.

#endif