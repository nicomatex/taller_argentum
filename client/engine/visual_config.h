#ifndef __VISUAL_CONFIG_H
#define __VISUAL_CONFIG_H

/* Tamanios en centesimas de tile */

/* Configuraciones en formato {WIDTH, HEIGHT, X_OFFSET, Y_OFFSET}*/
#define HEAD_CONFIG {60,60,20,-186}
#define BODY_CONFIG {100,180,0,-40}
#define WEAPON_CONFIG {100,180,0,-40}
#define SHIELD_CONFIG {100,180,0,-40}

#define FLOOR_TILE_CONFIG {100,100,0,0}

#define NAME_TEXT_CONFIG {0,70,-85,0}
#define NAME_TEXT_FONT_ID 1
#define NAME_COLOR {255,255,255,255}
#define MAX_NAME_LEN 15

#define PATTERN_TILE_SIZE 32 //Los tiles patron tienen 32px. 
#define NPC_SIZE_FACTOR 1.3 //Para hacer los npcs mas grandes.

#endif