#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "../SDL/sdl_timer.h"
#include "../ECS/component.h"
#include <mutex>

class PositionComponent: public Component {
   private:
	int x;
	int y;
	std::mutex m;
	
   public:
   	PositionComponent();
	PositionComponent(int x, int y);
	~PositionComponent();
	void init() override;
	void update() override;
	void draw() override;
	int get_x() const;
	int get_y() const;
	void set_position(int x, int y);
};

#endif