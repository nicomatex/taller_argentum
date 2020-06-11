#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "../SDL/sdl_timer.h"
#include "../ECS/component.h"

class PositionComponent: public Component {
   private:
	int x;
	int y;



   public:
   	PositionComponent();
	PositionComponent(int x, int y);
	~PositionComponent();
	void init() override;
	void update() override;
	void draw() override;
	int get_x();
	int get_y();
	void set_position(int x, int y);
};

#endif