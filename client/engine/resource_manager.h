#ifndef __RESOURCE_MANAGER_H
#define __RESOURCE_MANAGER_H
#include <unordered_map>

#include "SDL/sdl_animated_sprite.h"
#include "SDL/sdl_music.h"
#include "SDL/sdl_sfx.h"
#include "SDL/sdl_texture.h"
#include "SDL/sdl_texture_loader.h"
#include "SDL/sdl_bitmap_font.h"
#include "SDL2/SDL_ttf.h"
#include "animation_pack.h"

/* ----- Tipos y forward declarations ----- */
typedef std::unordered_map<std::string, std::unordered_map<int, SDLTexture>>
    TextureMap;

typedef std::unordered_map<std::string, std::unordered_map<int, AnimationPack>>
    AnimationPackMap;

typedef std::unordered_map<std::string, std::unordered_map<int, SDLSprite>>
    SpriteMap;

typedef std::unordered_map<int, TTF_Font*> FontMap;

typedef std::unordered_map<int, SDLMusic> MusicMap;

typedef std::unordered_map<int, SDLSoundFx> SoundFxMap;

typedef std::unordered_map<int, SDLBitmapFont> BitmapFontMap;
/**
 * @brief Singleton para el manager de texturas.
 *
 */
class ResourceManager {
   private:
    TextureMap texture_map;
    AnimationPackMap animation_pack_map;
    SpriteMap sprite_map;
    FontMap font_map;
    BitmapFontMap bitmap_font_map;
    MusicMap music_map;
    SoundFxMap sound_fx_map;
    ResourceManager();

    /**
     * @brief Realiza la carga de texturas.
     *
     * @param loader Loader con el cual se van a cargar las texturas.
     * @param texture_index_file archivo de indice que contiene
     * las rutas e informacion de las texturas a cargar.
     */
    void _load_textures(SDLTextureLoader& loader,
                        const std::string& texture_index_file);

    /**
     * @brief Realiza la generacion de sprites.
     *
     * @param sprite_index_file Archivo de indice que contiene
     * toda la informacion de las sprites a generar.
     */
    void _load_animations(const std::string& sprite_index_file);

    /**
     * @brief Realiza la carga de fuentes.
     *
     * @param font_index_file Archivo de indice que contiene
     * las rutas e informacion de cada fuente.
     */
    void _load_fonts(const std::string& font_index_file);

    /**
     * @brief Realiza la carga de archivos de audio.
     *
     * @param audio_index_file Archivo de indice
     * que contiene la informacion de los archivos de audio.
     */
    void _load_audio(const std::string& audio_index_file);

   public:
    ~ResourceManager();

    /**
     * @brief Devuelve la instancia del resource manager.
     *
     * @return ResourceManager&
     */
    static ResourceManager& get_instance();
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;

    /**
     * @brief Obtiene una textura.
     *
     * @param type Tipo de la textura a obtener.
     * @param id Id de la textura, dentro del tipo.
     * @return SDLTexture&
     */
    SDLTexture& get_texture(const std::string& type, int id);

    /**
     * @brief Devuelve un pack de animacion.
     *
     * @param type Tipo del pack de animacion.
     * @param id Id del pack de animacion, dentro de su tipo.
     * @return AnimationPack&
     */
    AnimationPack& get_animation_pack(const std::string& type, int id);

    /**
     * @brief Devuelve un sprite.
     *
     * @param type Tipo del sprite a obtener.
     * @param id Id del sprite, dentro de su tipo.
     * @return SDLSprite&
     */
    SDLSprite& get_sprite(const std::string& type, int id);

    /**
     * @brief Devuelve una fuente de SDL.
     *
     * @param id Id de la fuente.
     * @return TTF_Font*
     */
    TTF_Font* get_font(int id);

    SDLBitmapFont& get_bitmap_font(int id);

    /**
     * @brief Devuelve un objeto SDLMusic.
     *
     * @param id id de la musica a obtener.
     * @return SDLMusic&
     */
    SDLMusic& get_music(int id);

    /**
     * @brief Devuelve un objeto SDLSoundFx
     *
     * @param id Id del efecto de sonido.
     * @return SDLSoundFx&
     */
    SDLSoundFx& get_sound_fx(int id);

    /**
     * @brief Libera recursos alocados por el manager.
     *
     */
    void free_resources();

    /**
     * @brief Realiza la carga a memoria de todos los assets. Solo debe ser
     * llamado una vez
     *
     * @param loader Loader a partir del cual se cargaran las texturas.
     */
    void init(SDLTextureLoader& loader);


};

#endif