#include"Sprite.h"
#include"Amoeba.h"
#include"Metaball2DGroup.h"
#include <time.h>
#include <string>

class AI : Amoeba
{
	/*
		Metaball2DGroup balls;
		std::string identifier;
		double velX, velY;
		double px, py;
		int radAngle;
		double radius;
		bool normal;


		
		Metaball2DGroup *attackArm;
		bool attackActive;
		time_t attackArmTimer;

		int attackSpacing1;
		int attackSpacing2;
		int attackSpacing3;

		float lslope;

		Metaball2DGroup *defendArm;

		bool defendActive;
		bool defendSegActive;
		bool defendSeg2Active;
		time_t defendArmTimer;

		int defendSpacing1;
		int defendSpacing2;
		int defendSpacing3;

		float rslope;

		double attackFistPx;
		double attackFistPy;
		double attackFistRadius;

		double defendFistPx;
		double defendFistPy;
		double defendFistRadius;

		bool isCollision;
		bool isBody;
		bool isDefend; 
		bool isAttack;
		bool isWall;

		double colPx;
		double colPy;
		double colAngle;
*/

		public:

		AI(double,double, double, bool);
	
		
		void update(){};

		void update(Sprite* player)
		{
			if(!isCollision)
			{
				if(player->getPx() > px)
				{
					velX = 0.1;
				}
				else
				{
					velX = -0.1;
				}

				if(player->getPy() > py)
				{
					velY = 0.1;
				}
				else
				{
					velY = -0.1;
				}
			}


			px += velX;
			py += velY;

			
			
			//retractArm();
			
			balls.shiftGroup(velX, velY);	
			
		};

		void collision(Sprite *obj)
		{

			velX = 0;
			velY = 0;

			if(isBody)
			{

				colPx = obj->getPx();
				colPy = obj->getPy();

				colAngle = (-1) * ( ( py - colPy) / (px - colPx));

				//printf("[%f: %f]" , colPx, colPy);
				//printf("[%f: %f]" , px, py);

				if(px < colPx && py < colPy)
				{
					velX = -2;
					velY = -2;
					//canMoveDown = false;
					//canMoveRight = false;
					//canMoveUp = true;
					//canMoveLeft = true;
				}
				else if( px < colPx && py > colPy)
				{
					velX = -2;
					velY = 2;
					//canMoveRight = false;
					//canMoveUp = false;
					//canMoveDown = true;
					//canMoveLeft = true;
				}
				else if(px > colPx && py < colPy)
				{
					velX = 2;
					velY = -2;
					//canMoveDown = false;
					//canMoveLeft = false;
					//canMoveUp = true;
					//canMoveRight = true;
				}
				else if(px > colPx && py > colPy)
				{
					velX = 2;
					velY = 2;
					//canMoveLeft = false;
					//canMoveUp = false;
					//canMoveDown = true;
					//canMoveRight = true;
				}
				else if(px == colPx && py < colPy)
				{
					velX = 2;
					velY = -2;
					//canMoveDown = false;
					//canMoveRight = true;
					//canMoveLeft = true;
					//canMoveUp = true;
				}
				else if(px == colPx && py > colPy)
				{
					velX = 2;
					velY = 2;
					//canMoveUp = false;
					//canMoveRight = true;
					//canMoveLeft = true;
					//canMoveDown = true;
				}
				else if( px < colPx && py == colPy)
				{
					velX = -2;
					velY = -2;
					//canMoveRight = false;
					//canMoveLeft = true;
					//canMoveDown = true;
					//canMoveUp = true;
				}
				else if( px > colPx && py == colPy)
				{
					velX = 2;
					velY = 2;
					//canMoveLeft = false;
					//canMoveRight = true;
					//canMoveDown = true;
					//canMoveUp = true;
				}
			}

		}

		

		
		void extendAttackArm()
		{
			
		}

		void extendDefendArm()
		{
			
		
		}
		
		void retractArm()
		{


		}
};