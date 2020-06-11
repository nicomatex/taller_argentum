#ifndef __RESOURCE_MANAGER_H
#define __RESOURCE_MANAGER_H
#include <unordered_map>

#include "SDL/sdl_animated_sprite.h"
#include "SDL/sdl_texture.h"
#include "SDL/sdl_texture_loader.h"
#include "animation_pack.h"

/* ----- Tipos y forward declarations ----- */
typedef std::unordered_map<std::string, std::unordered_map<int, SDLTexture>>
    TextureMap;

typedef std::unordered_map<std::string, std::unordered_map<int, AnimationPack>>
    AnimationPackMap;

typedef std::unordered_map<std::string, std::unordered_map<int, SDLSprite>>
    SpriteMap;

/* Singleton para el manager de texturas. */
class ResourceManager {
   private:
    TextureMap texture_map;
    AnimationPackMap animation_pack_map;
    SpriteMap sprite_map;
    ResourceManager();

    /* Realiza la carga de texturas indexadas en el texture_index_file, llenando
    el texture_map. */
    void _load_textures(SDLTextureLoader& loader,
                        const std::string& texture_index_file);

    /* Genera las animaciones indicadas en el sprite_index_file, llenando
    el animation_pack_map y el sprite_map */
    void _load_animations(const std::string& sprite_index_file);

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

    /* Realiza la carga y generacion de todos los sprites y sonidos.*/
    void init(SDLTextureLoader& loader);
};

#endif