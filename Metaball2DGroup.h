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

class Metaball2DGroup
{

private:
	double px,py;//point x and y
	std::list<Metaball2D>balls;
	std::list<Metaball2DGroup>subgroups;
	std::list<triangle>blocks[16];
	bool discovered [NUM_GRIDS][NUM_GRIDS];
	double values[NUM_GRIDS + 1][NUM_GRIDS + 1];
	int moves[16];

public:
	
	Metaball2DGroup(){

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

	void popSubgroup()
	{
		subgroups.pop_back();
	}

	std::pair<int,int> *getCentres( int *size){
		std::pair<int,int> *centres;
		if( ( centres = (std::pair<int,int>*) malloc( balls.size() * sizeof(std::pair<int,int>))) == NULL){
			printf("malloc failed\n");
			*size = 0;
			return NULL;
		}

		int i =0;
		for( std::list<Metaball2D>::iterator it = balls.begin(); it != balls.end(); it++){
			centres[i] = std::pair<int,int>( (int)floor( it->getPy() / GRID_SIZE), (int)floor( it->getPx() / GRID_SIZE));
			i++;
		}
		*size = i;
		return centres;
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

		for( int i = 0; i < NUM_GRIDS; i++){
			memset(discovered[i], false, NUM_GRIDS * sizeof(bool) ); 
			memset(values[i], -1.0, (NUM_GRIDS + 1) * sizeof(double));
		}
		memset(values[NUM_GRIDS], -1.0f, (NUM_GRIDS + 1) * sizeof(double));

		int gridRows = screenTop / GRID_SIZE;
		int gridCols = screenRight / GRID_SIZE;
		std::stack<std::pair<int,int>> spots;
		
		std::pair<int,int> *centres = NULL;
		int size;
		centres = getCentres( &size);
		for( int i = 0; i<size; i++){
			discovered[centres[i].first][centres[i].second];
			spots.push( centres[i]);
		}
		free( centres);
		centres = NULL;

		for( std::list<Metaball2DGroup>::iterator it = subgroups.begin(); it != subgroups.end(); it++){
			centres = it->getCentres(&size);
			for( int i = 0; i<size; i++){
				if( 0 <= centres[i].first && centres[i].first < NUM_GRIDS && 0 <= centres[i].second && centres[i].second < NUM_GRIDS){
					discovered[centres[i].first][centres[i].second] = true;
					spots.push( centres[i]);
				}
			}
			free( centres);
			centres = NULL;
		}

		std::pair<int,int> v;
		while( !spots.empty() ){
			v = spots.top();
			spots.pop();
						int type = 0;
			bool pass = false;

			for( int y = v.first * GRID_SIZE; y <= (v.first + 1) * GRID_SIZE  && !pass && y >=0 && y <= screenTop ; y+= GRID_SIZE){
				for( int x = v.second * GRID_SIZE; x <= (v.second + 1) * GRID_SIZE && x >=0 && x <= screenRight; x+=GRID_SIZE){
					type = type << 1;
					if( values[y / GRID_SIZE][x / GRID_SIZE] >= 0.0f ){
						type |= values[y / GRID_SIZE][x / GRID_SIZE] >= THRESHOLD;
						continue;
					}

					double score = evaluatePoint(x,y);
					if(score >= THRESHOLD){
						type |= 1;
						values[y / GRID_SIZE][x / GRID_SIZE] = score;
						continue;
					}

					score += evaluateSubGroups(x, y);
					values[y / GRID_SIZE][x / GRID_SIZE] = score;
					if(score >= THRESHOLD ){
						type |= 1;
					}
					if( score <= 0.5){
						pass = true;
						break;
					} else if( score >= 2.0){
						type = 15;
						pass = true;
					}
				}
			}
	
			int type2 = 0;
			for( int i=0; i<4; i++){
				type2 <<= 1;
				type2 |= type & 1;
				type >>= 1;
			}
			type = type2;

			glBegin(GL_TRIANGLES);
			for( std::list<triangle>::iterator it = blocks[type].begin(); it != blocks[type].end(); it++){
				for( int i = 0; i < 3; i++)
					glVertex2i( GRID_SIZE * v.second + it->points[i].x, GRID_SIZE * v.first + it->points[i].y);  
			}
			glEnd();
			
			if( moves[type] & 1 &&  v.first + 1 < NUM_GRIDS){
				if( !discovered[ v.first + 1][v.second] ){
					discovered[ v.first + 1][v.second] = true;
					spots.push( std::pair<int,int>(v.first + 1, v.second));
				}
			}
			if( moves[type] & 2 && v.second + 1 < NUM_GRIDS){
				if( !discovered[ v.first][v.second + 1] ){
					discovered[ v.first][v.second + 1] = true;
					spots.push( std::pair<int,int>(v.first, v.second + 1));
				}
			}
			if( moves[type] & 4 && v.first - 1 >= 0){
				if( !discovered[ v.first - 1][v.second] ){
					discovered[ v.first - 1][v.second] = true;
					spots.push( std::pair<int,int>(v.first - 1, v.second));
				}
			}
			if( moves[type] & 8 && v.second - 1 >= 0){
				if( !discovered[v.first][v.second - 1] ){
					discovered[v.first][v.second - 1] = true;
					spots.push( std::pair<int,int>(v.first, v.second  - 1));
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