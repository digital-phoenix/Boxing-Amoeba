#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include"Sprite.h"

class Obstacle : Sprite  {
	public:
		void draw(){};
		bool collision(Sprite*){};
		void update(){};
};

#endif