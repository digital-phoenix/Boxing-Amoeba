#ifndef AMOEBA_H_
#define AMOEBA_H_

#include"Sprite.h"
#include"Metaball2DGroup.h"
#include <time.h>

class Amoeba : Sprite  {
	private:
		Metaball2DGroup balls;
		double velX, velY;
		double px, py;
		double radAngle;

		Metaball2DGroup *armBall;
		bool armActive;
		bool segActive;
		bool seg2Active;

		int spacing1;
		int spacing2;
		int spacing3;

		time_t armTimer;

		int rightMx, rightMy;
		int leftMx, leftMy;
		float slope;

	public:

		Amoeba();
		
		void draw(){
			balls.draw();
		};

		bool collision(Sprite*){ return false;};

		void update()
		{
			px += velX;
			py += velY;
			balls.shiftGroup(velX, velY);	
		};

		void setVelx( double x){
			velX = x;
		}

		void setVely( double y){
			velY = y;
		}

		void setRightMousePos(GLsizei x, GLsizei y)
		{
			rightMx = x;
			rightMy = y;
		}

	    void setLeftMousePos(GLsizei x, GLsizei y)
		{
			if(!armActive)
			{
				leftMx = x;
				leftMy = y;
			}
		
		}

		void setVelocity( double x, double y){
			setVelx(x);
			setVely(y);
		}

		void incAngle()
		{
			radAngle+=20;
		}

		void decAngle()
		{
			radAngle-=20;
		}


		void extendArm()
		{
			if(slope == 0)
			{
				printf("%d - %f\n", leftMy, py);
				printf("%d - %f\n", leftMx, px);

			    slope = (-1) * ( ( leftMy - py) / (leftMx - px) );

				if(leftMx < px)
				{
					spacing1 = -50;
					spacing2 = -80;
					spacing3 = -100;
					
				}
				else
				{
					spacing1 = 50;
					spacing2 = 80;
					spacing3 = 100;
				}
			
				printf("%f", slope);
			}
			//printf("%f",slope);

			/*Can make general case for more arm segments*/
			if(!armActive)
			{
				armActive = true;
				armTimer = time(NULL);
			    armBall = new Metaball2DGroup();
				armBall->addMetaball(new Metaball2D(px + spacing1, py + slope * (spacing1), 5.0 ));
				balls.addSubgroup(armBall);
				armBall->popMetaball();
				
			}
			else if(armActive)
			{
				
				if(time(NULL) - armTimer > 1 && !segActive)
				{
					segActive = true;
					balls.popSubgroup();
					armBall->addMetaball(new Metaball2D(px+spacing1, py+ slope*(spacing1),5.0 ));
					armBall->addMetaball(new Metaball2D(px+spacing2, py+ slope*(spacing2),5.0));
					balls.addSubgroup(armBall);
					armBall->popMetaball();
					armBall->popMetaball();
					
				}
				else if(time(NULL) - armTimer > 2 && !seg2Active)
				{
					seg2Active = true;
					balls.popSubgroup();
					armBall->addMetaball(new Metaball2D(px + spacing1, py + slope *(spacing1), 5.0 ));
					armBall->addMetaball(new Metaball2D(px + spacing2, py + slope*(spacing2),5.0));
					armBall->addMetaball(new Metaball2D(px + spacing3, py + slope*(spacing3),5.0));
					balls.addSubgroup(armBall);

					armBall->popMetaball();
					armBall->popMetaball();
					armBall->popMetaball();
					
				}
			}
			
		}

		void retractArm()
		{
			if(armActive)
			{
				balls.popSubgroup();
				slope = 0;
				armBall = NULL;
				armActive = false;
				segActive = false;
				seg2Active = false;
			}

		}
};

#endif