#ifndef METABALL2DGROUP_H_
#define METABALL2DGROUP_H_

#include "Sprite.h"
#include "Metaball2D.h"
#include "GraphicState.h"
#include <list>
#include <vector>
#include <stack>

#define THRESHOLD 1.0f
#define GRID_SIZE 4
#define DEBUG 0
#define NUM_GRIDS 500 / GRID_SIZE
#define SQRT2 1.41421356237
#define PI 3.14159265359

typedef struct{
	Metaball2D ball;
	int r,g,b;
	bool cleared;
}MetaballDrawData;

class Metaball2DGroup
{

private:
	double px,py;//point x and y
	std::list<Metaball2D>balls;
	std::list<Metaball2DGroup>subgroups;
	std::list<triangle>blocks[16];
	bool discovered [NUM_GRIDS][NUM_GRIDS];
	double values[NUM_GRIDS + 1][NUM_GRIDS + 1];
	int r,g,b;
	int moves[16];
	double minRadius;

public:
	
	Metaball2DGroup(){

		r = 255; 
		g = 0;
		b = 0;

		minRadius = 1000;

		triangle triangles[34];

		moves[0] = 0;
		blocks[0] = std::list<triangle>();

		triangles[0].points[0].x = 0.0f;
		triangles[0].points[0].y = 0.0f;		
		triangles[0].points[1].x = GRID_SIZE / 2.0f;
		triangles[0].points[1].y = 0.0f;
		triangles[0].points[2].x = 0.0f;
		triangles[0].points[2].y = GRID_SIZE / 2.0f;
		blocks[1] = std::list<triangle>( triangles, triangles + 1);
		moves[1] = 12;

		triangles[1].points[0].x = GRID_SIZE / 2.0f;
		triangles[1].points[0].y = 0.0f;
		triangles[1].points[1].x = GRID_SIZE;
		triangles[1].points[1].y = 0.0f;
		triangles[1].points[2].x = GRID_SIZE;
		triangles[1].points[2].y = GRID_SIZE / 2.0f;
		blocks[2] = std::list<triangle>( triangles + 1, triangles + 2);
		moves[2] = 6;

		triangles[2].points[0].x = 0.0f;
		triangles[2].points[0].y = 0.0f;
		triangles[2].points[1].x = GRID_SIZE;
		triangles[2].points[1].y = GRID_SIZE / 2.0f;
		triangles[2].points[2].x = 0.0f;
		triangles[2].points[2].y = GRID_SIZE / 2.0f;
		triangles[3].points[0].x = 0.0f;
		triangles[3].points[0].y = 0.0f;
		triangles[3].points[1].x = GRID_SIZE;
		triangles[3].points[1].y = 0.0f;
		triangles[3].points[2].x = GRID_SIZE;
		triangles[3].points[2].y = GRID_SIZE / 2.0f;
		blocks[3] = std::list<triangle>( triangles + 2, triangles + 4);
		moves[3] = 14;

		triangles[14].points[0].x = 0;
		triangles[14].points[0].y = GRID_SIZE;
		triangles[14].points[1].x = 0;
		triangles[14].points[1].y = GRID_SIZE / 2.0f;
		triangles[14].points[2].x = GRID_SIZE / 2.0f;
		triangles[14].points[2].y = GRID_SIZE;
		blocks[4] = std::list<triangle>( triangles + 14, triangles + 15);
		moves[4] = 9;

		triangles[15].points[0].x = GRID_SIZE / 2.0f;
		triangles[15].points[0].y = 0.0f;
		triangles[15].points[1].x = 0.0f;
		triangles[15].points[1].y = GRID_SIZE;
		triangles[15].points[2].x = 0.0f;
		triangles[15].points[2].y = 0.0f;
		triangles[16].points[0].x = GRID_SIZE / 2.0f;
		triangles[16].points[0].y = GRID_SIZE;
		triangles[16].points[1].x = 0.0f;
		triangles[16].points[1].y = GRID_SIZE;
		triangles[16].points[2].x = GRID_SIZE / 2.0f;
		triangles[16].points[2].y = 0.0f;
		blocks[5] = std::list<triangle>( triangles + 15, triangles + 17);
		moves[5] = 13;

		triangles[17] = triangles[1];
		triangles[18] = triangles[14];

		triangles[19].points[0].x = GRID_SIZE / 2.0f;
		triangles[19].points[0].y = GRID_SIZE;
		triangles[19].points[1].x = 0.0f;
		triangles[19].points[1].y = GRID_SIZE / 2.0f;
		triangles[19].points[2].x = GRID_SIZE / 2.0f;
		triangles[19].points[2].y = 0.0f;

		triangles[20].points[0].x = GRID_SIZE / 2.0f;
		triangles[20].points[0].y = GRID_SIZE;
		triangles[20].points[1].x = GRID_SIZE;
		triangles[20].points[1].y = GRID_SIZE / 2.0f;
		triangles[20].points[2].x = GRID_SIZE / 2.0f;
		triangles[20].points[2].y = 0.0f;		
		blocks[6] = std::list<triangle>( triangles + 17, triangles + 21);
		moves[6] = 15;

		triangles[21].points[0].x = 0.0f;
		triangles[21].points[0].y = GRID_SIZE;
		triangles[21].points[1].x = GRID_SIZE;
		triangles[21].points[1].y = GRID_SIZE / 2.0f;
		triangles[21].points[2].x = GRID_SIZE /2.0f;
		triangles[21].points[2].y = GRID_SIZE;

		triangles[22].points[0].x = 0.0f;
		triangles[22].points[0].y = GRID_SIZE;
		triangles[22].points[1].x = GRID_SIZE;
		triangles[22].points[1].y = 0.0f;
		triangles[22].points[2].x = GRID_SIZE;
		triangles[22].points[2].y = GRID_SIZE / 2.0f;

		triangles[23].points[0].x = 0.0f;
		triangles[23].points[0].y = GRID_SIZE;
		triangles[23].points[1].x = 0.0f;
		triangles[23].points[1].y = 0.0f;
		triangles[23].points[2].x = GRID_SIZE;
		triangles[23].points[2].y = 0.0f;
		blocks[7] = std::list<triangle>( triangles + 21, triangles + 24);
		moves[7] = 4;

		triangles[4].points[0].x = GRID_SIZE / 2.0f;
		triangles[4].points[0].y = GRID_SIZE;
		triangles[4].points[1].x = GRID_SIZE;
		triangles[4].points[1].y = GRID_SIZE / 2.0f;
		triangles[4].points[2].x = GRID_SIZE;
		triangles[4].points[2].y = GRID_SIZE;
		blocks[8] = std::list<triangle>( triangles + 4, triangles + 5);
		moves[8] = 3;

		triangles[5] = triangles[4];
		triangles[6] = triangles[0];
		triangles[7].points[0].x = GRID_SIZE / 2.0f;
		triangles[7].points[0].y = 0.0f;
		triangles[7].points[1].x = GRID_SIZE / 2.0f;
		triangles[7].points[1].y = GRID_SIZE;
		triangles[7].points[2].x = 0.0f;
		triangles[7].points[2].y = GRID_SIZE /2.0f;
		triangles[8].points[0].x = GRID_SIZE / 2.0f;
		triangles[8].points[0].y = 0.0f;
		triangles[8].points[1].x = GRID_SIZE;
		triangles[8].points[1].y = GRID_SIZE /2.0f;
		triangles[8].points[2].x = GRID_SIZE / 2.0f;
		triangles[8].points[2].y = GRID_SIZE;
		blocks[9] = std::list<triangle>( triangles + 5, triangles + 9);
		moves[9] = 15;

		triangles[9].points[0].x = GRID_SIZE;
		triangles[9].points[0].y = 0.0f;
		triangles[9].points[1].x = GRID_SIZE;
		triangles[9].points[1].y = GRID_SIZE;
		triangles[9].points[2].x = GRID_SIZE / 2.0f;
		triangles[9].points[2].y = 0.0f;
		triangles[10].points[0].x = GRID_SIZE;
		triangles[10].points[0].y = GRID_SIZE;
		triangles[10].points[1].x = GRID_SIZE /2.0f;
		triangles[10].points[1].y = GRID_SIZE;
		triangles[10].points[2].x = GRID_SIZE / 2.0f;
		triangles[10].points[2].y = 0.0f;
		blocks[10] = std::list<triangle>( triangles + 9, triangles + 11);
		moves[10] = 7;
		
		triangles[11].points[0].x = 0.0f;
		triangles[11].points[0].y = GRID_SIZE / 2.0f;
		triangles[11].points[1].x = 0.0f;
		triangles[11].points[1].y = 0.0f;
		triangles[11].points[2].x = GRID_SIZE;
		triangles[11].points[2].y = 0.0f;
		triangles[12].points[0].x = 0.0f;
		triangles[12].points[0].y = GRID_SIZE / 2.0f;
		triangles[12].points[1].x = GRID_SIZE;
		triangles[12].points[1].y = 0.0f;
		triangles[12].points[2].x = GRID_SIZE /2.0f;
		triangles[12].points[2].y = GRID_SIZE;
		triangles[13].points[0].x = GRID_SIZE /2.0f;
		triangles[13].points[0].y = GRID_SIZE;
		triangles[13].points[1].x = GRID_SIZE;
		triangles[13].points[1].y = 0.0f;
		triangles[13].points[2].x = GRID_SIZE;
		triangles[13].points[2].y = GRID_SIZE;
		blocks[11] = std::list<triangle>( triangles + 11, triangles + 14);
		moves[11] = 15;

		triangles[24].points[0].x = 0.0f;
		triangles[24].points[0].y = GRID_SIZE;
		triangles[24].points[1].x = 0.0f;
		triangles[24].points[1].y = GRID_SIZE / 2.0f;
		triangles[24].points[2].x = GRID_SIZE;
		triangles[24].points[2].y = GRID_SIZE / 2.0f;
		triangles[25].points[0].x = 0.0f;
		triangles[25].points[0].y = GRID_SIZE;
		triangles[25].points[1].x = GRID_SIZE;
		triangles[25].points[1].y = GRID_SIZE / 2.0f;
		triangles[25].points[2].x = GRID_SIZE;
		triangles[25].points[2].y = GRID_SIZE;
		blocks[12] = std::list<triangle>( triangles + 24, triangles + 26);
		moves[12] = 11;

		triangles[26].points[0].x = 0.0f;
		triangles[26].points[0].y = GRID_SIZE;
		triangles[26].points[1].x = GRID_SIZE;
		triangles[26].points[1].y = GRID_SIZE / 2.0f;
		triangles[26].points[2].x = GRID_SIZE;
		triangles[26].points[2].y = GRID_SIZE;

		triangles[27].points[0].x = 0.0f;
		triangles[27].points[0].y = GRID_SIZE;
		triangles[27].points[1].x = GRID_SIZE / 2.0f;
		triangles[27].points[1].y = 0.0f;
		triangles[27].points[2].x = GRID_SIZE;
		triangles[27].points[2].y = GRID_SIZE / 2.0f;

		triangles[28].points[0].x = 0.0f;
		triangles[28].points[0].y = GRID_SIZE;
		triangles[28].points[1].x = 0.0f;
		triangles[28].points[1].y = 0.0f;
		triangles[28].points[2].x = GRID_SIZE / 2.0f;
		triangles[28].points[2].y = 0.0f;
		blocks[13] = std::list<triangle>( triangles + 26, triangles + 29);
		moves[13] = 15;

		triangles[29].points[0].x = 0.0f;
		triangles[29].points[0].y = GRID_SIZE;
		triangles[29].points[1].x = 0.0f;
		triangles[29].points[1].y = GRID_SIZE / 2.0f;
		triangles[29].points[2].x = GRID_SIZE;
		triangles[29].points[2].y = GRID_SIZE;
		triangles[30].points[0].x = 0.0f;
		triangles[30].points[0].y = GRID_SIZE / 2.0f;
		triangles[30].points[1].x = GRID_SIZE / 2.0f;
		triangles[30].points[1].y = 0.0f;
		triangles[30].points[2].x = GRID_SIZE;
		triangles[30].points[2].y = GRID_SIZE;
		triangles[31].points[0].x = GRID_SIZE;
		triangles[31].points[0].y = GRID_SIZE;
		triangles[31].points[1].x = GRID_SIZE / 2.0f;
		triangles[31].points[1].y = 0.0f;
		triangles[31].points[2].x = GRID_SIZE;
		triangles[31].points[2].y = 0.0f;
		blocks[14] = std::list<triangle>( triangles + 29, triangles + 32);
		moves[14] = 15;

		triangles[32].points[0].x = 0.0f;
		triangles[32].points[0].y = 0.0f;
		triangles[32].points[1].x = GRID_SIZE;
		triangles[32].points[1].y = 0.0f;
		triangles[32].points[2].x = GRID_SIZE;
		triangles[32].points[2].y = GRID_SIZE;

		triangles[33].points[0].x = 0.0f;
		triangles[33].points[0].y = 0.0f;
		triangles[33].points[1].x = GRID_SIZE;
		triangles[33].points[1].y = GRID_SIZE;
		triangles[33].points[2].x = 0.0f;
		triangles[33].points[2].y = GRID_SIZE;
		blocks[15] = std::list<triangle>( triangles + 32, triangles + 34);
		moves[15] = 15;

	}

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
	
	void getRGB( int *r, int *g, int *b){
		*r = this->r;
		*g = this->g;
		*b = this->b;
	}

	std::vector<MetaballDrawData> getDrawData(){
		std::vector<MetaballDrawData> ballData;
		if( subgroups.size() > 1){
			ballData = subgroups.front().getDrawData();
		}
		for( std::list<Metaball2DGroup>::iterator it = subgroups.begin(); it != subgroups.end(); it++){
			std::vector<MetaballDrawData> other = it->getDrawData();
			for( int i=0; i < other.size(); i++){
				ballData.push_back( other[i]);
			}
		}
		
		MetaballDrawData data;
		for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
			data.ball = *it;
			data.r = r;
			data.g = g;
			data.b = b;
			data.cleared = false;
			ballData.push_back(data);
		}
		return ballData;
	}

	void popSubgroup()
	{
		subgroups.pop_back();
	}

	double evaluatePoint(double x, double y){
		double score =0;
		for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
			score += it->Equation(x,y);
			if( score >= THRESHOLD){
				return score;
			}
		}
		return score;
	}

	double calculatePoint( double  x, double y, std::vector<MetaballDrawData> &data){
		double score = 0;
		for( int i = 0; i < data.size(); i++){
			score += data[i].ball.Equation(x, y);
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

	void calcTangent( double x, double y, double *tx, double *ty, std::vector<MetaballDrawData> &data){

		*tx = 0;
		*ty = 0;
		double tmpx, tmpy;

		for( int i = 0; i < data.size(); i++){
			data[i].ball.calcTangent(x, y, &tmpx, &tmpy);
			*tx += tmpx;
			*ty += tmpy;
		}
		
	}

	double findSmallestRadius( std::vector<MetaballDrawData> &data){
		double min = 10000.0;
		double tmp;

		for( int i = 0; i < data.size(); i++){
			if( min > ( tmp = data[i].ball.getRadius() ) ){
				min = tmp;
			}
		}

		return min;
	}

	void calcNormal( double x, double y, double *tx, double *ty, std::vector<MetaballDrawData> &data){
		*tx = 0;
		*ty = 0; 

		double tmpx, tmpy;

		for( int i = 0; i < data.size(); i++){
			data[i].ball.calcNormal(x, y, &tmpx, &tmpy);
			*tx += tmpx;
			*ty += tmpy;
		}

	}
	
	std::pair<double,double> stepOnceTowardsBorder(std::pair<double,double> start, double force, std::vector<MetaballDrawData> &data){
		std::pair<double, double> norm;
		calcNormal( start.first, start.second, &norm.first, &norm.second, data);

		double mag = sqrt( norm.second * norm.second + norm.first * norm.first);
		if( abs(mag) > 0.0001){
			norm.first /= mag;
			norm.second /= mag;
		}

		if( abs(norm.first) < 0.0001 && abs(norm.second) < 0.0001){
			norm.first = 0.0001;
			norm.second = 0.0001;
		}

		double stepSize = minRadius / THRESHOLD - ( minRadius / force) + 0.01;
		norm.first *= stepSize;
		norm.second *= stepSize;
		
		norm.first += start.first;
		norm.second += start.second;

		return norm;
	}

	std::pair<double, double> findBorder( std::pair<double,double> start, std::vector<MetaballDrawData> &data){
		double force;
		while( ( force = calculatePoint( start.first, start.second, data) ) > THRESHOLD){
			start = stepOnceTowardsBorder( start, force, data);
		}
		return start;
	}

	std::pair<double, double> traceBorder( std::pair<double,double> start, double stepSize, std::vector<MetaballDrawData> &data){
		std::pair<double, double> res;
		calcTangent( start.first, start.second, &res.first, &res.second, data);

		double mag = sqrt( res.first * res.first+ res.second * res.second);
		if( mag > 0.0001){
			res.first /= mag;
			res.second /= mag;
		}

		res.first *= stepSize / 2.0;
		res.second *= stepSize / 2.0;
		calcTangent( start.first + res.first, start.second + res.second, &res.first, &res.second, data);

		mag = sqrt( res.first * res.first+ res.second * res.second);
		if( mag > 0.0001){
			res.first /= mag;
			res.second /= mag;
		}

		res.first *= stepSize;
		res.second *= stepSize;
		res.first = start.first + res.first;
		res.second = start.second + res.second;
		res = stepOnceTowardsBorder(res, calculatePoint(res.first, res.second, data), data );
		return res;
	}

	void drawCircle( double x, double y, double radius){
		glBegin( GL_TRIANGLES);
		double newX;
		double newY;
		double lastX = radius + x;
		double lastY = y;

		for( double i = 1.0; i <= 360; i++){
			newX = cos( i * PI / 180.0) * radius + x;
			newY = sin( i * PI / 180.0) * radius + y;

			glVertex2d( lastX, lastY);
			glVertex2d( newX, newY);
			glVertex2d( x, y);
		}
		glEnd();
	}

	void draw(){
		int ballsCleared = 0;
		std::vector<MetaballDrawData> ballData = getDrawData();
		std::pair<double, double> start;
		std::pair<double, double> lastPoint;
		std::pair<double, double> nextPoint;
		minRadius = findSmallestRadius(ballData);
		double min = 5000.0;
		double min2 = min;
		double tmp;
		int closest;
		int closest2nd;
		
		for( int i=0; i<ballData.size(); i++){
			if( ballData[i].cleared ){
				continue;
			}

			start = findBorder( std::pair<double,double>(ballData[i].ball.getPx() + ballData[i].ball.getRadius(), ballData[i].ball.getPy()), ballData);
			lastPoint = start;
			for( int j =0; j < 500; j++){
				nextPoint = traceBorder( lastPoint, 5, ballData);
				min = 5000.0;
				min2 = min;
				closest = 0;
				closest2nd = -1;
				for( int k=0; k < ballData.size(); k++){
					if( min > (tmp = ( nextPoint.first - ballData[k].ball.getPx()) * ( nextPoint.first - ballData[k].ball.getPx()) + ( nextPoint.second - ballData[k].ball.getPy()) * ( nextPoint.second - ballData[k].ball.getPy()) )){
						min = tmp;
						closest = k;
					}
				}
				ballData[closest].cleared = true;

				glColor3f(1.0, 0, 0);
				glBegin( GL_TRIANGLES);
				closest = 0;
				if( lastPoint.first * ballData[closest].ball.getPy() - lastPoint.second * ballData[closest].ball.getPx() + lastPoint.second * nextPoint.first
					- lastPoint.first * nextPoint.second + ballData[closest].ball.getPx() * nextPoint.second - nextPoint.first * ballData[closest].ball.getPy() > 0.00001){
					
					glVertex2d( lastPoint.first, lastPoint.second);
					glVertex2d( nextPoint.first, nextPoint.second);
					glVertex2d( ballData[closest].ball.getPx(), ballData[closest].ball.getPy());

				} else{
					glVertex2d( nextPoint.first, nextPoint.second);
					glVertex2d( lastPoint.first, lastPoint.second);
					glVertex2d( ballData[closest].ball.getPx(), ballData[closest].ball.getPy());
				}
				glEnd();

				tmp =  (start.first - nextPoint.first) * (start.first - nextPoint.first) + (start.second - nextPoint.second) * (start.second - nextPoint.second);
				if( tmp < 20){

					glBegin( GL_TRIANGLES);
					if( start.first * ballData[closest].ball.getPy() - start.second * ballData[closest].ball.getPx() + start.second * nextPoint.first
						- start.first * nextPoint.second + ballData[closest].ball.getPx() * nextPoint.second - nextPoint.first * ballData[closest].ball.getPy() > 0.00001){

						glVertex2d( nextPoint.first, nextPoint.second);		
						glVertex2d( start.first, start.second);
						glVertex2d( ballData[closest].ball.getPx(), ballData[closest].ball.getPy());

					} else{
						glVertex2d( start.first, start.second);
						glVertex2d( nextPoint.first, nextPoint.second);
						glVertex2d( ballData[closest].ball.getPx(), ballData[closest].ball.getPy());
					}
					glEnd();
					
					break;
				}

				lastPoint = nextPoint;
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