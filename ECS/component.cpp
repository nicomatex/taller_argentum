#include "component.h"

Component::Component() {}

Component::~Component() {}

void Component::setEntity(Entity *entity) {
	this->entity = entity;
}
