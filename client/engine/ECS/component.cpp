#include "component.h"

Component::Component() {}

Component::~Component() {}

void Component::set_entity(Entity *entity) {
	this->entity = entity;
}
