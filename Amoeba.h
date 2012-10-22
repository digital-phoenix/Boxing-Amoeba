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
		int radAngle;

		Metaball2DGroup *attackArm;

		bool attackActive;
		bool attackSegActive;
		bool attackSeg2Active;
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


			}
	

			/*Can make general case for more arm segments*/
			if(!attackActive)
			{
				attackActive = true;
				attackArmTimer = time(NULL);
				attackArm = new Metaball2DGroup();
				attackArm->addMetaball(new Metaball2D(px + attackSpacing1, py + lslope * (attackSpacing1), 5.0 ));
				balls.addSubgroup(attackArm);
				attackArm->popMetaball();

			}
			else if(attackActive)
			{

				if(time(NULL) - attackArmTimer > 0.25 && !attackSegActive)
				{
					attackSegActive = true;
					balls.popSubgroup();
					attackArm->addMetaball(new Metaball2D(px+ attackSpacing1, py+ lslope*(attackSpacing1),5.0 ));
					attackArm->addMetaball(new Metaball2D(px+ attackSpacing2, py+ lslope*(attackSpacing2),5.0));
					balls.addSubgroup(attackArm);
					attackArm->popMetaball();
					attackArm->popMetaball();

				}
				else if(time(NULL) - attackArmTimer > 0.75 && !attackSeg2Active)
				{
					attackSeg2Active = true;
					balls.popSubgroup();
					attackArm->addMetaball(new Metaball2D(px + attackSpacing1, py + lslope *(attackSpacing1), 5.0 ));
					attackArm->addMetaball(new Metaball2D(px + attackSpacing2, py + lslope*(attackSpacing2),5.0));
					attackArm->addMetaball(new Metaball2D(px + attackSpacing3, py + lslope*(attackSpacing3),5.0));
					balls.addSubgroup(attackArm);

					attackArm->popMetaball();
					attackArm->popMetaball();
					attackArm->popMetaball();

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

			}

			if(!defendActive)
			{
				defendActive = true;
				defendArmTimer = time(NULL);
				defendArm = new Metaball2DGroup();
				defendArm->addMetaball(new Metaball2D(px + defendSpacing1, py + rslope * (defendSpacing1), 5.0 ));
				balls.addSubgroup(defendArm);
				defendArm->popMetaball();

			}
			else if(defendActive)
			{

				if(time(NULL) - defendArmTimer > 0.25 && !defendSegActive)
				{
					defendSegActive = true;
					balls.popSubgroup();
					defendArm->addMetaball(new Metaball2D(px+ defendSpacing1, py+ rslope*(defendSpacing1),5.0 ));
					defendArm->addMetaball(new Metaball2D(px+ defendSpacing2, py+ rslope*(defendSpacing2),5.0));
					balls.addSubgroup(defendArm);
					defendArm->popMetaball();
					defendArm->popMetaball();

				}
				else if(time(NULL) - defendArmTimer > 0.75 && !defendSeg2Active)
				{
					defendSeg2Active = true;
					balls.popSubgroup();
					defendArm->addMetaball(new Metaball2D(px + defendSpacing1, py + rslope *(defendSpacing1), 5.0 ));
					defendArm->addMetaball(new Metaball2D(px + defendSpacing2, py + rslope*(defendSpacing2),5.0));
					defendArm->addMetaball(new Metaball2D(px + defendSpacing3, py + rslope*(defendSpacing3),5.0));
					balls.addSubgroup(defendArm);

					defendArm->popMetaball();
					defendArm->popMetaball();
					defendArm->popMetaball();

				}
			}


		}
		

		void retractArm()
		{
			if(attackActive)
			{
				balls.popSubgroup();
				lslope = 0;
				attackArm = NULL;
				attackActive = false;
				attackSegActive = false;
				attackSeg2Active = false;
			}

			if(defendActive)
			{
				balls.popSubgroup();
				rslope = 0;
				defendArm = NULL;
				defendActive = false;
				defendSegActive = false;
				defendSeg2Active = false;
			}

		}
};

#endif