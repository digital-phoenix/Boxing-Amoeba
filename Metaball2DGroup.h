#ifndef METABALL2DGROUP_H_
#define METABALL2DGROUP_H_

#include "Sprite.h"
#include "Metaball2D.h"
#include "GraphicState.h"
#include <list>

#define THRESHOLD 1.0f

class Metaball2DGroup
{

private:
	double px,py;//point x and y
	std::list<Metaball2D>balls;

public:

	Metaball2DGroup(){}

	void addMetaball(Metaball2D* ball){
		balls.push_back(*ball);
	}

	void draw(){
		glBegin(GL_POINTS);
		for( int y = SCREEN_BOTTOM; y <= SCREEN_TOP; y++){
			for( int x = SCREEN_LEFT; x <= SCREEN_RIGHT; x++){
				int score = 0;
				for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
					score += it->Equation(x,y);
					if( score >= THRESHOLD){
						glVertex2i(x,y);
					}
				}
			}
		}
		glEnd();
	}

	void shiftGroup(double x, double y){
		for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
			it->shift(x, y);
		}
	}
};

#endif