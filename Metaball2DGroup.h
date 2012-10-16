#ifndef METABALL2DGROUP_H_
#define METABALL2DGROUP_H_

#include "Sprite.h"
#include "Metaball2D.h"
#include "GraphicState.h"
#include <list>

#define THRESHOLD 1.0f
#define GRID_SIZE 20

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
		
		int gridRows = screenTop / GRID_SIZE;
		int gridCols = screenRight / GRID_SIZE;

		for( int row = 0; row < gridRows; row++){
			for( int col = 0; col < gridCols; col++){

				if( checkSamples( col * GRID_SIZE, row * GRID_SIZE)){

					for( int y = row * GRID_SIZE; y <= (row + 1) * GRID_SIZE; y++){
						for( int x = col * GRID_SIZE; x <= (col + 1) * GRID_SIZE; x++){

							int score = 0;

							for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){

								score += it->Equation(x,y);
								if( score >= THRESHOLD){
									glVertex2i(x,y);
									continue;
								}
							}
						}
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

	inline bool checkSamples( int x, int y){
		int score = 0;
		for( int i = 0; i < 2; i++){
			for( int j = 0; j < 2; j++){
				for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
					score += it->Equation(x + GRID_SIZE * i, y + GRID_SIZE * j);
					if( score >= 0.5){
						return true;
					}
				}
			}
		}

		for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
			score += it->Equation(x + GRID_SIZE / 2, y + GRID_SIZE / 2);
			if( score >= 0.5){
				return true;
			}
		}
		return false;
	}
};

#endif