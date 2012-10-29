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

		AI(double,double, double, double, bool);
	
		
		void update(){};

		void update(Sprite* player)
		{

			double distance = sqrt(  ((py - player->getPy()) * (py - player->getPy()) ) +  ((px - player->getPx() ) * (px - player->getPx() ))) ; 

			if(distance < radius + player->getRadius() + 50)//Approximate arm distance needed to attack 
			{
				int x = rand()%2;

				if(x == 0)
				{
					extendAttackArm(player);
				}
				else
				{
					extendDefendArm(player);
				}

			}

			if(!isCollision)
			{

				if(player->getPx() > px)
				{
					velX = 0.2;
				}
				else
				{
					velX = -0.2;
				}

				if(player->getPy() > py)
				{
					velY = 0.2;
				}
				else
				{
					velY = -0.2;
				}

			}


			px += velX;
			py += velY;

			
			needToResize = false;

			retractArm();
			
			balls.shiftGroup(velX, velY);	
			
		};

		void collision(Sprite *obj)
		{

			velX = 0;
			velY = 0;


			if(isDefend)
			{
					colPx = colPx + obj->getPx();
					colPy = colPy + obj->getPy();

					if(px < colPx)
					{
						velX = -50;
					}
					else
					{
						velX = 50;
					}

					if(py < colPy)
					{
						velY = -50;
					}
					else
					{
						velY = 50;
					}
					
			}
			else if(isAttack)
			{
				needToResize = true;

			}
			else if(isBody)
			{

				colPx = obj->getPx();
				colPy = obj->getPy();

				//colAngle = (-1) * ( ( py - colPy) / (px - colPx));

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

	void extendAttackArm(Sprite *player)
		{
			if(lslope == 0)
			{
			
				lslope = ( ( player->getPy() - py) / (player->getPx() - px) );
				double angle = atan(lslope);
				

				//double angle = radian * 180/3.1415962;
				//printf("%f\n", angle);

				if(player->getPx() < px)
				{
					attackSpacing1 = -70;
					attackSpacing2 = -90;
					attackSpacing3 = -110;
				}
				else
				{
					attackSpacing1 = 70;
					attackSpacing2 = 90;
					attackSpacing3 = 110;
				}
						

				
				if(!attackActive)
				{
						attackActive = true;
						attackArmTimer = time(NULL);

						attackArm = new Metaball2DGroup();
						attackArm->addMetaball(new Metaball2D(px + cos(angle)*attackSpacing1, py + sin(angle)*attackSpacing1, scale*3.0));
						attackArm->addMetaball(new Metaball2D(px + cos(angle) *attackSpacing2, py + sin(angle)*attackSpacing2,scale*3.0));
						attackArm->addMetaball(new Metaball2D(px + cos(angle)* attackSpacing3, py + sin(angle)*attackSpacing3,scale*3.0));
						balls.addSubgroup(attackArm);

						attackFistPx = px + cos(angle)*attackSpacing3;
						attackFistPy = py + sin(angle)*attackSpacing3;
						attackFistRadius = scale*3;

				}	
			}
		}

		void extendDefendArm(Sprite* player)
		{
			if(rslope == 0)
			{

				rslope =( ( player->getPy() - py) / (player->getPx() - px) );
				double angle = atan(rslope);

				if(player->getPx() < px)
				{
					defendSpacing1 = -70;
					defendSpacing2 = -90;
					defendSpacing3 = -130;
				}
				else
				{
					defendSpacing1 = 70;
					defendSpacing2 = 90;
					defendSpacing3 = 130;
				}

				if(!defendActive && (defendWaitTimer - time(NULL) <= 0 ))
				{
						defendActive = true;
						defendArmTimer = time(NULL);
						defendWaitTimer = time(NULL) + 7;
						defendArm = new Metaball2DGroup();
				
						defendArm->addMetaball(new Metaball2D(px + cos(angle)* defendSpacing1, py + sin(angle) *defendSpacing1, scale*3.0));
						defendArm->addMetaball(new Metaball2D(px + cos(angle)* defendSpacing2, py + sin(angle) *defendSpacing2,scale*3.0));
						defendArm->addMetaball(new Metaball2D(px + cos(angle)* defendSpacing3, py + sin(angle)*defendSpacing3,scale*12.0));
						balls.addSubgroup(defendArm);

						defendFistPx = px + cos(angle)*defendSpacing3;
						defendFistPy = py + sin(angle)*defendSpacing3;
						defendFistRadius = scale*12;
				}
				else
				{
					rslope = 0;
				}
			}


		}
		
	
};