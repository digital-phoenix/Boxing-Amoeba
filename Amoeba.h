#ifndef AMOEBA_H_
#define AMOEBA_H_

#include"Sprite.h"
#include"Metaball2DGroup.h"
#include <string>
#include <time.h>

class Amoeba : public Sprite  {
	protected:

		/*Characteristics*/
		std::string identifier;
		Metaball2DGroup balls;
		double velX, velY;
		double px, py;
		int radAngle;
		double radius;
		bool normal;


		/*Arm management variables*/
		Metaball2DGroup *attackArm;
		bool attackActive;
		time_t attackArmTimer;

		int attackSpacing1;
		int attackSpacing2;
		int attackSpacing3;

	    int leftMx, leftMy;
		float lslope;

		Metaball2DGroup *defendArm;

		bool defendActive;
		bool defendSegActive;
		bool defendSeg2Active;
		time_t defendArmTimer;

		int defendSpacing1;
		int defendSpacing2;
		int defendSpacing3;

		int rightMx, rightMy;
		float rslope;

		double attackFistPx;
		double attackFistPy;
		double attackFistRadius;

		double defendFistPx;
		double defendFistPy;
		double defendFistRadius;


		/*Collision gathering variables*/
		bool isCollision;
		bool isBody;
		bool isDefend;
		bool isAttack;
		bool isWall;

		double colPx;
		double colPy;
		double colAngle;

		bool canMoveUp;
		bool canMoveDown;
		bool canMoveLeft;
		bool canMoveRight;
		

	public:
		Amoeba();
		Amoeba(double,double, double, bool);
		
		void draw(){
			balls.draw();
		};

		bool checkCollision(Sprite* obj)
		{ 
			//(y2 - y1)² + (x2 - x1)²
			
			double distance = sqrt(  ((py - obj->getPy()) * (py - obj->getPy()) ) +  ((px - obj->getPx() ) * (px - obj->getPx() ))) ; 

			if(distance < radius + obj->getRadius() )
			{
				isCollision = true;
				isBody = true;

				return true;
			}

			double *attackData; 
			attackData = obj->getAttackData();
			
			if(attackData[0] != 0 && attackData[2] == 3)
			{
				
				distance = sqrt(((py - attackData[1] ) * (py - attackData[1]) +  ((px - attackData[0]) * (px - attackData[0])))) ; 
			
				colPx = attackData[0];
				colPy = attackData[1];

				if(distance < radius + attackData[2])
				{
					printf("%f:  %f", distance, radius + attackData[2]);
					isCollision = true;
					isAttack = true;

					return true;
				}
			}


			isCollision = false;
			isBody = false;
			isAttack = false;
			isDefend = false;
			isWall = false;

			return false;
		
		};

		bool* getAvailableMoves()
		{
			bool moves[] = {canMoveUp, canMoveDown, canMoveLeft, canMoveRight};
			return moves;
		}

		double* getAttackData()
		{
			double attack[] = { attackFistPx, attackFistPy, attackFistRadius};
			return attack;
		}

		double* getDefendData()
		{
			double defend[] = { defendFistPx, defendFistPy, defendFistRadius};
			return defend;

		}

		void update(Sprite* s){ }

		void update()
		{
			px += velX;
			py += velY;

			if(!isCollision)
			{
				 canMoveUp = true;
				 canMoveDown = true;
				 canMoveLeft = true;
				 canMoveRight = true;
			}

			/*glTranslate(player1X, player2Y, 0);
			glRotatef(angle1 * (180/PI), 0, 0, 1);
			glutSolidSphere(10, 20,20);
			if (keyStates['e']){
			  attack();
			 }
			glRotatef(-(angle1 * (180/PI)), 0, 0, 1);
			 glTranslatef(-p1X, -p1Y,0);
			 */
			
			retractArm();
			balls.shiftGroup(velX, velY);	
		}

		std::string getIdentifier()
		{
			return identifier;
		}

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
					canMoveDown = false;
					canMoveRight = false;
					//canMoveUp = true;
					//canMoveLeft = true;
				}
				else if( px < colPx && py > colPy)
				{
					canMoveRight = false;
					canMoveUp = false;
					//canMoveDown = true;
					//canMoveLeft = true;
				}
				else if(px > colPx && py < colPy)
				{
					canMoveDown = false;
					canMoveLeft = false;
					//canMoveUp = true;
					//canMoveRight = true;
				}
				else if(px > colPx && py > colPy)
				{
					canMoveLeft = false;
					canMoveUp = false;
					//canMoveDown = true;
					//canMoveRight = true;
				}
				else if(px == colPx && py < colPy)
				{
					canMoveDown = false;
					//canMoveRight = true;
					//canMoveLeft = true;
					//canMoveUp = true;
				}
				else if(px == colPx && py > colPy)
				{
					canMoveUp = false;
					//canMoveRight = true;
					//canMoveLeft = true;
					//canMoveDown = true;
				}
				else if( px < colPx && py == colPy)
				{
					canMoveRight = false;
					//canMoveLeft = true;
					//canMoveDown = true;
					//canMoveUp = true;
				}
				else if( px > colPx && py == colPy)
				{
					canMoveLeft = false;
					//canMoveRight = true;
					//canMoveDown = true;
					//canMoveUp = true;
				}
			}
			else if(isAttack)
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
		}

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

		double getRadius()
		{
			return radius;
		}

		double getPx()
		{
			return px;
		}

		double getPy()
		{
			return py;
		}

		
		void setRightMousePos(GLsizei x, GLsizei y)
		{
			if(!defendActive)
			{
				rightMx = x;
				rightMy = y;
			}
		}

		void setLeftMousePos(GLsizei x, GLsizei y)
		{
			if(!attackActive)
			{
				leftMx = x;
				leftMy = y;
			}
		}

			void incAngle()
			{
				radAngle+=20;
			}

			void decAngle()
			{
				radAngle-=20;
			}

		void extendAttackArm()
		{
			if(lslope == 0)
			{
			
				lslope = ( ( leftMy - py) / (leftMx - px) );


				if(leftMx < px)
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
						attackArm->addMetaball(new Metaball2D(px + cos(lslope)*attackSpacing1, py + sin(lslope)*(attackSpacing1), 3.0 ,true));
						attackArm->addMetaball(new Metaball2D(px + cos(lslope) *attackSpacing2, py + sin(lslope)*(attackSpacing2),3.0, true));
						attackArm->addMetaball(new Metaball2D(px + cos(lslope)* attackSpacing3, py + sin(lslope)*(attackSpacing3),3.0, true));
						balls.addSubgroup(attackArm);

						attackFistPx = px + cos(lslope)*attackSpacing3;
						attackFistPy = py + sin(lslope)*attackSpacing3;
						attackFistRadius = 3;

				}	
			}
		}
		

			
		



		void extendDefendArm()
		{
			if(rslope == 0)
			{

				rslope = (-1) * ( ( rightMy - py) / (rightMx - px) );

				if(rightMx < px)
				{
					defendSpacing1 = -70;
					defendSpacing2 = -90;
					defendSpacing3 = -110;

					
				}
				else
				{
					defendSpacing1 = 70;
					defendSpacing2 = 90;
					defendSpacing3 = 110;


				}

				if(!defendActive)
				{
						defendActive = true;
						defendArmTimer = time(NULL);
						defendArm = new Metaball2DGroup();
				
						defendArm->addMetaball(new Metaball2D(px + cos(rslope)* defendSpacing1, py + sin(rslope) *(defendSpacing1), 3.0 ,false));
						defendArm->addMetaball(new Metaball2D(px + cos(rslope)* defendSpacing2, py + sin(rslope) *(defendSpacing2),3.0, false));
						defendArm->addMetaball(new Metaball2D(px + cos(rslope)* defendSpacing3, py + sin(rslope)*(defendSpacing3),3.0 , false));
						balls.addSubgroup(defendArm);

						defendFistPx = px + cos(rslope)*defendSpacing3;
						defendFistPy = py + sin(rslope)*defendSpacing3;
						defendFistRadius = 3;
				}
			}


		}
		

		void retractArm()
		{
			if(attackActive && time(NULL) - attackArmTimer > 0.25)
			{
				attackFistPx = 0;
				attackFistPy = 0;
				balls.popSubgroup();
				lslope = 0;
				attackArm = NULL;
				attackActive = false;
			}

			if(defendActive && time(NULL) - defendArmTimer > 7)
			{
				balls.popSubgroup();
				rslope = 0;
				defendArm = NULL;
				defendActive = false;

			}

		}
};

#endif