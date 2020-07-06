#ifndef __ENGINE_CONFIG_H
#define __ENGINE_CONFIG_H

/* Offset de transicion */
#define MOVEMENT_OFFSET 100
#define MOVEMENT_TRANSITION_TIME 200

/* Constantes de transformacion */
#define OFFSET_GRANULARITY 100
#define SIZE_GRANULARITY 100

#define TEXTURE_INDEX_FILE "ind/textures.json"
#define SPRITE_INDEX_FILE "ind/sprites.json"
#define FONT_INDEX_FILE "ind/fonts.json"
#define AUDIO_INDEX_FILE "ind/audio.json"

/* Mensajes de carga */
#define MSG_TEXTURES_LOADING "Cargando texturas..."
#define MSG_TEXTURES_FINISHED "Carga finalizada!"

/* Mensajes de errores */
#define MSG_ERR_LOADING_TEXTURE "Error cargando la textura."
#define MSG_ERR_MAP_NOT_INITIALIZED "El mapa no fue inicializado."

/* Sonidos */
#define MAX_CONCURRENT_SOUNDS 3
#define SOUND_TIMEOUT 200 //Tiempo cada el cual se libera un slot de sonido.

/* Indices */
#define TILESET_ID_INDEX 0
#endif
