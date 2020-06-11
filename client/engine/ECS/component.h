#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
   protected:
    Entity *entity;
   public:
   	Component();
   	virtual ~Component();
   	void set_entity(Entity *entity);
   	/*
		Inicializa el componente con lo que necesite, es llamado en el momento
		de agregarlo a la entity.
   	*/
   	virtual void init() = 0;
   	/*
		Actualiza la información del componente.
   	*/
   	virtual void update() = 0;
   	/*
		Muestra por pantalla el componente.
   	*/
   	virtual void draw() = 0;
};

#endif // COMPONENT_H
