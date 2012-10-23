#include"Sprite.h"
#include"Metaball2DGroup.h"
#include <time.h>

class AI : Sprite
{
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

		AI(double,double, double, bool);
		
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
				return true;
			}

			isCollision = false;
			return false;
		
		};


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