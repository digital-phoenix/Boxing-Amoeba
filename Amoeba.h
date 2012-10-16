#ifndef AMOEBA_H_
#define AMOEBA_H_

#include"Sprite.h"
#include"Metaball2DGroup.h"

class Amoeba : Sprite  {
	private:
		Metaball2DGroup balls;
		double velX, velY;

	public:

		Amoeba();
		
		void draw(){
			balls.draw();
		};

		bool collision(Sprite*){ return false;};

		void update(){
			balls.shiftGroup(velX, velY);		
		};

		void setVelx( double x){
			velX = x;
		}

		void setVely( double y){
			velY = y;
		}

		void setVelocity( double x, double y){
			setVelx(x);
			setVely(y);
		}
};

#endif