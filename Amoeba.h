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

		Metaball2DGroup *armBall;
		bool armActive;
		bool segActive;
		bool seg2Active;
		time_t armTimer;


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

		void setVelocity( double x, double y){
			setVelx(x);
			setVely(y);
		}

		void extendArm()
		{
			/*Can make general case for more arm segments*/
			if(!armActive)
			{
				armActive = true;
				armTimer = time(NULL);
			    armBall = new Metaball2DGroup();
				armBall->addMetaball(new Metaball2D(px+100.0,py+10,5.0 ));
				balls.addSubgroup(armBall);
				armBall->popMetaball();
				
			}
			else if(armActive)
			{
				
				if(time(NULL) - armTimer > 1 && !segActive)
				{
					puts("seg");
					segActive = true;
					balls.popSubgroup();
					armBall->addMetaball(new Metaball2D(px+100.0,py+10,5.0 ));
					armBall->addMetaball(new Metaball2D(px+130.0,py+20,5.0));
					balls.addSubgroup(armBall);
					armBall->popMetaball();
					armBall->popMetaball();
					
				}
				else if(time(NULL) - armTimer > 2 && !seg2Active)
				{
					puts("seg2");
					seg2Active = true;
					balls.popSubgroup();
					armBall->addMetaball(new Metaball2D(px+100.0,py+10,5.0 ));
					armBall->addMetaball(new Metaball2D(px+130.0,py+20,5.0));
					armBall->addMetaball(new Metaball2D(px+150.0,py+10,5.0));
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
				armBall = NULL;
				armActive = false;
				segActive = false;
				seg2Active = false;
			}

		}
};

#endif