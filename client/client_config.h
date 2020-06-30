#ifndef __CLIENT_CONFIG_H
#define __CLIENT_CONFIG_H

/* Archivos */
#define CLIENT_CONFIG_FILE "config.json"

/* Misc*/
#define WINDOW_TITLE "Argentum Online"

/* Mensajes*/
#define MSG_ERR_CONFIG_FILE "Error parseando el archivo de configuracion."
#define MSG_ERR_CONECT_DROPPED "Conexion cerrada."

/* Configuraciones de estilo de la UI */
// --- Chat ---
#define CHAT_FONT "assets/fonts/arial.ttf"
#define CHAT_INPUT_FONT_COLOR {255,255,255,255}
#define CHAT_INPUT_BACKGROUND_COLOR {50,50,50,255}
#define CHAT_BOX_FONT_COLOR {49, 168, 63,255}
#define CHAT_BOX_BACKGROUND_COLOR {0,0,0,255}

// --- Barras de estado --- 
#define HP_BAR_COLOR {205, 0, 0, 255}
#define MP_BAR_COLOR {16,0,200,255}

#define STAT_BAR_FONT_COLOR {255,255,255,255}

// --- Items Equipados ---
#define POS_HELMET 0
#define POS_ARMOR 1
#define POS_SHIELD 2
#define POS_WEAPON 3

/* Layout de la interfaz */
#define MAIN_WINDOW_WIDTH 1138
#define MAIN_WINDOW_HEIGHT 640
 
// --- Chat ---
#define VIEWPORT_MAIN_RENDER {0, 128, 878, 512}
#define VIEWPORT_CHAT {0,0,878,128}
#define AREA_CHAT {0,0,878,128}
#define CHAT_LINES 8

// --- Panel lateral ---
#define VIEWPORT_SIDE_PANEL {878,0,260,640}
#define AREA_SIDE_PANEL {0, 0, 260, 640}

#define HP_BAR_AREA {65, 576, 129, 15}
#define MP_BAR_AREA {65, 616, 129, 15}

#define EQUIPPED_ITEMS_AREA {205,296,45,181}

#define CAST_BUTTON_AREA {64,514,131,37}

/* Fuentes */
#define CHAT_FONT_ID 1 
#define STAT_FONT_ID 1


/* Configuracion de la camara */
#define TILE_SIZE 32
#define VIEWPORT_WIDTH 28
#define VIEWPORT_HEIGHT 16
#define CAMERA_SPEED 3

#endif