# include "AI.h"

AI::AI(double px, double py, double radius,double scale, Amoeba* player, bool normal)
{
	velX = 0;
	velY = 0;

	this->player = player;
	this->px = px;
	this->py = py;
	this->radius = radius*scale;
	this->normal = normal;
	this->scale = scale;

	needToResize = false;

	attackArm = NULL;

	attackActive = false;
	attackArmTimer = 0;
	attackSpacing1 = 0;
	attackSpacing2 = 0;
	attackSpacing3 = 0;

	lslope = 0;

	defendArm = NULL;

	defendActive = false;
	defendSegActive = false;
	defendSeg2Active = false;
	defendArmTimer = 0;

	defendSpacing1 = 0;
	defendSpacing2 = 0;
	defendSpacing3 = 0;

	rslope = 0;


	isCollision = false;
	colPx = 0;
    colPy = 0;
	colAngle = 0;


	isBody = false;
	isDefend = false;
	isAttack = false;
	isWall = false;

	balls.addMetaball(new Metaball2D(this->px,this->py,this->radius));//body of AI
}

void AI::update(){

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

	Amoeba::update();
}					
