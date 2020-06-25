#ifndef __CLIENT_CONFIG_H
#define __CLIENT_CONFIG_H

/* Archivos */
#define CLIENT_CONFIG_FILE "config.json"

/* Misc*/
#define WINDOW_TITLE "Argentum Online"

/* Mensajes*/
#define MSG_ERR_CONFIG_FILE "Error parseando el archivo de configuracion."
#define MSG_ERR_CONECT_DROPPED "Conexion cerrada."

/* Configuraciones de la UI */
#define CHAT_FONT "assets/fonts/arial.ttf"
#define CHAT_INPUT_FONT_COLOR {255,255,255,255}
#define CHAT_INPUT_BACKGROUND_COLOR {50,50,50,255}
#define CHAT_BOX_FONT_COLOR {49, 168, 63,255}
#define CHAT_BOX_BACKGROUND_COLOR {0,0,0,255}

/* Layout de la interfaz */

#define MAIN_WINDOW_WIDTH 960
#define MAIN_WINDOW_HEIGHT 640

#define AREA_MAIN_RENDER {0, 128, 700, 512}
#define AREA_CHAT {0,0,700,128}
#define AREA_SIDE_PANEL {700,0,260,960}

#define CHAT_LINES 8

/* Configuracion de la camara */
#define TILE_SIZE 32
#define VIEWPORT_WIDTH 22
#define VIEWPORT_HEIGHT 16
#define CAMERA_SPEED 3

#endif