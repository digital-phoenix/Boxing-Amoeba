#include"Sprite.h"

class Obstacle : Sprite  {
	public:
		virtual void draw() = 0;
		virtual bool collision(Sprite*) = 0;
		virtual void update() = 0;
};