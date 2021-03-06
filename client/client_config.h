#ifndef __CLIENT_CONFIG_H
#define __CLIENT_CONFIG_H

/* Archivos */
#define CONFIG_FILE "config.json"

/* Configuracion basica */

#define BASE_CONFIG_FILE                                                  \
    "{ \"server\": \"localhost\",\"port\": \"27016\",\"fullscreen\": "    \
    "false,\"window_width\":1138,\"window_height\":640, \"vsync\":true, " \
    "\"fps\":60}"

/* Misc*/
#define WINDOW_TITLE "Argentum Online"

/* Mensajes*/
#define MSG_ERR_CONFIG_FILE "Error parseando el archivo de configuracion."
#define MSG_ERR_CONECT_DROPPED "Conexion cerrada."

/* Configuraciones de estilo de la UI */
// --- Chat ---
#define CHAT_FONT "assets/fonts/arial.ttf"
#define CHAT_INPUT_FONT_COLOR \
    { 255, 255, 255, 255 }
#define CHAT_INPUT_BACKGROUND_COLOR \
    { 50, 50, 50, 255 }
#define CHAT_BOX_FONT_COLOR \
    { 49, 168, 63, 255 }
#define CHAT_BOX_BACKGROUND_COLOR \
    { 0, 0, 0, 255 }

// --- Barras de estado ---
#define HP_BAR_COLOR \
    { 205, 0, 0, 255 }
#define MP_BAR_COLOR \
    { 16, 0, 200, 255 }
#define XP_BAR_COLOR \
    { 47, 145, 0, 255 }
#define STAT_BAR_FONT_COLOR \
    { 255, 255, 255, 255 }

// --- Items Equipados ---
#define POS_HELMET 0
#define POS_ARMOR 1
#define POS_SHIELD 2
#define POS_WEAPON 3

/* Layout de la interfaz */
#define MAIN_WINDOW_WIDTH 1138
#define MAIN_WINDOW_HEIGHT 640

#define HELP_PANEL_AREA \
    { 169, 110, 800, 420 }

// --- Chat ---
#define VIEWPORT_MAIN_RENDER \
    { 0, 128, 878, 512 }
#define VIEWPORT_CHAT \
    { 0, 0, 878, 128 }
#define AREA_CHAT \
    { 0, 0, 878, 128 }
#define CHAT_LINES 8

// --- Panel lateral ---
#define VIEWPORT_SIDE_PANEL \
    { 878, 0, 260, 640 }
#define AREA_SIDE_PANEL \
    { 0, 0, 260, 640 }

#define HP_BAR_AREA \
    { 65, 592, 129, 15 }
#define MP_BAR_AREA \
    { 65, 616, 129, 15 }
#define XP_BAR_AREA \
    { 65, 130, 129, 15 }

#define EQUIPPED_ITEMS_AREA \
    { 205, 296, 45, 181 }
#define INVENTORY_AREA \
    { 19, 296, 180, 136 }
#define EQUIPMENT_ROWS 4
#define EQUIPMENT_COLS 1
#define INVENTORY_ROWS 3
#define INVENTORY_COLS 4
#define INVENTORY_SLOTS INVENTORY_ROWS* INVENTORY_COLS
#define INVENTORY_QTIES_COLOR \
    { 0, 200, 0, 255 }
#define INVENTORY_QTIES_FONT_ID 1

#define CAST_BUTTON_AREA \
    { 64, 540, 131, 37 }

#define GOLD_TEXT_AREA \
    { 85, 435, 114, 25 }
#define GOLD_TEXT_COLOR \
    { 218, 182, 6, 255 }

#define LEVEL_TEXT_AREA \
    { 131, 75, 23, 33 }

#define LEVEL_TEXT_COLOR \
    { 39, 135, 0, 255 }

#define SPELL_TEXT_AREA \
    { 65, 510, 129, 20 }
#define ATT_PTS_TEXT_AREA \
    { 154, 200, 40, 15 }
#define DEF_PTS_TEXT_AREA \
    { 154, 221, 40, 15 }

#define ITEM_NAME_AREA \
    { 19, 463, 180, 19 }

#define INFO_TEXT_COLOR \
    { 255, 255, 255, 255 }

// ---- Pantalla de login ----

#define LOGIN_VIEWPORT \
    { 0, 0, 1138, 640 }
#define LOGIN_BACKGROUND_AREA \
    { 0, 0, 1138, 640 }
#define USERNAME_INPUT_AREA \
    { 465, 392, 265, 30 }
#define USERNAME_INPUT_FONT_COLOR \
    { 255, 255, 255, 255 }
#define USERNAME_INPUT_BG_COLOR \
    { 85, 85, 85, 255 }

#define LOGIN_BUTTON_AREA \
    { 530, 435, 140, 28 }
#define CREATE_CHAR_BUTTON_AREA \
    { 50, 559, 140, 39 }

#define LOGIN_VIEW_ALERT_AREA \
    { 290, 510, 640, 60 }

#define ALERT_ID_WRONG_NAME 22
#define ALERT_ID_ALREADY_ONLINE 20

// ----- Pantalla de creacion de personaje ----
#define CHAR_CREATION_VIEWPORT \
    { 0, 0, 1138, 640 }
#define CHAR_CREATION_BACKGROUND_AREA \
    { 0, 0, 1138, 640 }
#define CHAR_CREATION_NAME_BG_COLOR \
    { 85, 85, 85, 255 }
#define CHAR_CREATION_NAME_AREA \
    { 446, 530, 242, 25 }

#define HUMAN_BUTTON_AREA \
    { 47, 120, 105, 96 }
#define ELF_BUTTON_AREA \
    { 47, 233, 105, 96 }
#define DWARF_BUTTON_AREA \
    { 47, 348, 105, 96 }
#define GNOME_BUTTON_AREA \
    { 47, 465, 105, 96 }

#define MAGE_BUTTON_AREA \
    { 943, 121, 105, 96 }
#define PRIEST_BUTTON_AREA \
    { 943, 234, 105, 96 }
#define PALADIN_BUTTON_AREA \
    { 943, 348, 105, 96 }
#define WARRIOR_BUTTON_AREA \
    { 943, 465, 105, 96 }

#define REQ_CHAR_CREATION_BUTTON_AREA \
    { 517, 568, 105, 29 }
#define GO_BACK_BUTTON_AREA \
    { 47, 596, 105, 29 }

#define RACE_DESCRIPTION_AREA \
    { 250, 29, 640, 120 }
#define CLASS_DESCRIPTION_AREA \
    { 250, 150, 640, 120 }

#define CHAR_PREVIEW_AREA \
    { 515, 270, 94, 170 }

#define HUMAN_INFO_TEX_ID 7
#define GNOME_INFO_TEX_ID 6
#define ELF_INFO_TEX_ID 5
#define DWARF_INFO_TEX_ID 4

#define MAGE_INFO_TEX_ID 8
#define PALADIN_INFO_TEX_ID 9
#define PRIEST_INFO_TEX_ID 10
#define WARRIOR_INFO_TEX_ID 11

#define HUMAN_PREVIEW_TEX_ID 15
#define GNOME_PREVIEW_TEX_ID 14
#define ELF_PREVIEW_TEX_ID 13
#define DWARF_PREVIEW_TEX_ID 12

#define MAGE_PREVIEW_TEX_ID 16
#define PALADIN_PREVIEW_TEX_ID 17
#define PRIEST_PREVIEW_TEX_ID 18
#define WARRIOR_PREVIEW_TEX_ID 19

#define CREATION_ALERT_AREA \
    { 249, 451, 640, 60 }
#define ALERT_ID_NAME_TAKEN 21

/* Fuentes */
#define CHAT_FONT_ID 1
#define STAT_FONT_ID 1
#define USERNAME_INPUT_FONT_ID 1

/* Configuracion de la camara */
#define TILE_SIZE 32
#define VIEWPORT_WIDTH 28
#define VIEWPORT_HEIGHT 16
#define CAMERA_SPEED 3

/* Misc */
#define DOUBLE_CLICK_DELAY 500  // in mseconds

#endif