#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

/**
 * @brief Componente agregable a entidades.
 * 
 */
class Component {
   protected:
    Entity *entity;

   public:
    Component();
    virtual ~Component();

    /**
     * @brief Le da una referencia al componente de la entidad a la que
     * pertenece.
     *
     * @param entity
     */
    void set_entity(Entity *entity);

    /**
     * @brief Inicializa el componente con lo que necesite, es llamado en el
     momento de agregarlo a la entity.
     *
     */
    virtual void init() = 0;
    
	/**
	 * @brief Actualiza el componente.
	 * 
	 */
    virtual void update() = 0;
};

#endif  // COMPONENT_H
