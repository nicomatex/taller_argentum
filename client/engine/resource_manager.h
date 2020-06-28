#ifndef __RESOURCE_MANAGER_H
#define __RESOURCE_MANAGER_H
#include <unordered_map>

#include "SDL/sdl_animated_sprite.h"
#include "SDL/sdl_texture.h"
#include "SDL/sdl_texture_loader.h"
#include "SDL/sdl_music.h"
#include "SDL/sdl_sfx.h"
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

/* Singleton para el manager de texturas. */
class ResourceManager {
   private:
    TextureMap texture_map;
    AnimationPackMap animation_pack_map;
    SpriteMap sprite_map;
    FontMap font_map;
    MusicMap music_map;
    SoundFxMap sound_fx_map;
    ResourceManager();

    /* Realiza la carga de texturas indexadas en el texture_index_file, llenando
    el texture_map. */
    void _load_textures(SDLTextureLoader& loader,
                        const std::string& texture_index_file);

    /* Genera las animaciones indicadas en el sprite_index_file, llenando
    el animation_pack_map y el sprite_map */
    void _load_animations(const std::string& sprite_index_file);

    /* Carga las fuentes para texto. */
    void _load_fonts(const std::string& font_index_file);

    /* Carga todos los archivos de audio. */
    void _load_audio(const std::string& audio_index_file);

   public:
    /* Devuelve la instancia */
    ~ResourceManager();
    static ResourceManager& get_instance();
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;

    /* Devuelve una referencia a la textura del tipo e id indicados. */
    SDLTexture& get_texture(const std::string& type, int id);

    /* Devuelve una referencia al pack de animacion del tipo e id indicados. */
    AnimationPack& get_animation_pack(const std::string& type, int id);

    /* Devuelve una referencia al sprite de tipo e id indicados. */
    SDLSprite& get_sprite(const std::string& type, int id);

    /* Devuelve la fuente con el id asociado solicitado. */
    TTF_Font* get_font(int id);

    /* Devuelve la musica asociada al id. */
    SDLMusic& get_music(int id);

    /* Devuelve el efecto de sonido asociado al id. */
    SDLSoundFx& get_sound_fx(int id);
    
    /* Debe ser llamado para liberar recursos que pueda
    haber alocado el manager.*/
    void free_resources();
    
    /* Realiza la carga y generacion de todos los sprites y sonidos.*/
    void init(SDLTextureLoader& loader);
};

#endif