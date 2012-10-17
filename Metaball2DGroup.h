
#ifndef METABALL2DGROUP_H_
#define METABALL2DGROUP_H_

#include "Sprite.h"
#include "Metaball2D.h"
#include "GraphicState.h"
#include <list>

#define THRESHOLD 1.0f
#define GRID_SIZE 30
#define DEBUG 1

class Metaball2DGroup
{

private:
	double px,py;//point x and y
	std::list<Metaball2D>balls;
	std::list<Metaball2DGroup>subgroups;
public:

	Metaball2DGroup(){}

	void addMetaball(Metaball2D* ball)
	{
		balls.push_back(*ball);
	}

	void popMetaball()
	{
		balls.pop_back();
	}
	
	void addSubgroup( Metaball2DGroup *other)
	{
		subgroups.push_back(*other);
	}

	void popSubgroup()
	{
		subgroups.pop_back();
	}

	double evaluatePoint(int x, int y){
		double score =0;
		for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
			score += it->Equation(x,y);
			if( score >= THRESHOLD){
				return score;
			}
		}
		return score;
	}

	double calculatePoint( int  x, int y){
		double score = 0;
		for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
			score += it->Equation(x,y);
		}
		return score;
	}

	double evaluateSubGroups( int x, int y){
		double score = 0;
		for( std::list<Metaball2DGroup>::iterator it = subgroups.begin(); it != subgroups.end(); it++){
			score += it->evaluatePoint(x, y);
			if( score >= THRESHOLD )
				return score;
		}
		return score;
	}

	void draw(){
		
		int gridRows = screenTop / GRID_SIZE;
		int gridCols = screenRight / GRID_SIZE;

		for( int row = 0; row < gridRows; row++){
			for( int col = 0; col < gridCols; col++){

				if( checkSamples( col * GRID_SIZE, row * GRID_SIZE)){
#if DEBUG == 1
					glColor4f(1.0f,0.0f,0.0f,0.5f);

					glBegin(GL_QUADS);
						glVertex2i( col * GRID_SIZE, row * GRID_SIZE);
						glVertex2i( (col + 1) * GRID_SIZE, row * GRID_SIZE);
						glVertex2i( (col + 1) * GRID_SIZE, (row + 1) * GRID_SIZE);
						glVertex2i( col * GRID_SIZE, (row + 1) * GRID_SIZE);
					glEnd();
#endif
					glColor4f(1.0f,1.0f,1.0f,0.5f);
					glBegin(GL_POINTS);

					for( int y = row * GRID_SIZE; y <= (row + 1) * GRID_SIZE; y++){
						for( int x = col * GRID_SIZE; x <= (col + 1) * GRID_SIZE; x++){
							double score = evaluatePoint(x,y);
							if(score >= THRESHOLD){
								glVertex2i(x,y);
								continue;
							}
							score += evaluateSubGroups(x, y);
							if(score >= THRESHOLD ){
								glVertex2i(x,y);
							}
						}
					}
					glEnd();

				}
			}
		}

	}

	void shiftGroup(double x, double y)
	{
		for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++)
		{
			it->shift(x, y);
		}

		for(std:: list<Metaball2DGroup>:: iterator it = subgroups.begin(); it != subgroups.end(); it++)
		{
			it->shiftGroup(x,y);
		}
	}

	inline bool checkSamples( int x, int y){
		double score;

		int sx = x + GRID_SIZE / 2;
		int sy = y + GRID_SIZE / 2;
		score = evaluatePoint(sx, sy);
		if( score >= 0.8){
			return true;
		} 
		score += evaluateSubGroups( sx, sy);
		if( score >= 0.8){
			return true;
		}

		return false;
	}
};

#endif