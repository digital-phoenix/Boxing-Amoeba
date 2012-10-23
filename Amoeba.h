#ifndef AMOEBA_H_
#define AMOEBA_H_

#include"Sprite.h"
#include"Metaball2DGroup.h"
#include <time.h>

class Amoeba : Sprite  {
	private:

		/*Characteristics*/
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


		/*Collision gathering variables*/
		bool isCollision;
		double colPx;
		double colPy;
		double colAngle;

		bool canMoveUp;
		bool canMoveDown;
		bool canMoveLeft;
		bool canMoveRight;
		

	public:

		Amoeba(double,double, double, bool);
		
		void draw(){
			balls.draw();
		};

		bool checkCollision(Sprite* obj)
		{ 
			//(y2 - y1)� + (x2 - x1)�
			
			double distance = sqrt(  ((py - obj->getPy()) * (py - obj->getPy()) ) +  ((px - obj->getPx() ) * (px - obj->getPx() ))) ; 

			if(distance < radius + obj->getRadius() )
			{
				isCollision = true;
				return true;
			}

			isCollision = false;
			return false;
		
		};

		bool* getAvailableMoves()
		{
			bool moves[] = {canMoveUp, canMoveDown, canMoveLeft, canMoveRight};
			return moves;
		}

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
		};

		void collision(Sprite *obj)
		{

			velX = 0;
			velY = 0;

			isCollision = true;

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
			
				lslope = (-1) * ( ( leftMy - py) / (leftMx - px) );


				if(leftMx < px)
				{
					attackSpacing1 = -50;
					attackSpacing2 = -80;
					attackSpacing3 = -100;	
				}
				else
				{
					attackSpacing1 = 50;
					attackSpacing2 = 80;
					attackSpacing3 = 100;

				}

				

				if(!attackActive)
				{
						attackActive = true;
						attackArmTimer = time(NULL);

						attackArm = new Metaball2DGroup();
						attackArm->addMetaball(new Metaball2D(px + cos(lslope)*attackSpacing1, py + sin(lslope)*(attackSpacing1), 4.0 ,true));
						attackArm->addMetaball(new Metaball2D(px + cos(lslope) *attackSpacing2, py + sin(lslope)*(attackSpacing2),4.0, true));
						attackArm->addMetaball(new Metaball2D(px + cos(lslope)* attackSpacing3, py + sin(lslope)*(attackSpacing3),4.0, true));
						balls.addSubgroup(attackArm);

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
					defendSpacing1 = -50;
					defendSpacing2 = -80;
					defendSpacing3 = -100;

					
				}
				else
				{
					defendSpacing1 = 50;
					defendSpacing2 = 80;
					defendSpacing3 = 100;


				}

				if(!defendActive)
				{
						defendActive = true;
						defendArmTimer = time(NULL);
						defendArm = new Metaball2DGroup();
				
						defendArm->addMetaball(new Metaball2D(px + cos(rslope)* defendSpacing1, py + sin(rslope) *(defendSpacing1), 5.0 ,false));
						defendArm->addMetaball(new Metaball2D(px + cos(rslope)* defendSpacing2, py + sin(rslope) *(defendSpacing2),5.0, false));
						defendArm->addMetaball(new Metaball2D(px + cos(rslope)* defendSpacing3, py + sin(rslope)*(defendSpacing3),5.0 , false));
						balls.addSubgroup(defendArm);
				}
			}


		}
		

		void retractArm()
		{
			if(attackActive && time(NULL) - attackArmTimer > 0.25)
			{
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