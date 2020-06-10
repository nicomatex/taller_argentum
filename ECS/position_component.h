#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "component.h"

class PositionComponent: public Component {
   private:
	int x;
	int y;
   public:
   	PositionComponent();
	PositionComponent(int x, int y);
	~PositionComponent();
	void init() override;
	void update(int dt) override;
	void draw() override;
	int get_x();
	int get_y();
};

#endif