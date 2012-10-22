#include"Amoeba.h"

Amoeba::Amoeba()
{
	velX = 0;
	velY = 0;

	px = 250;
	py = 250;

	attackArm = NULL;

	attackActive = false;
	attackSegActive = false;
	attackSeg2Active = false;
	attackArmTimer = 0;

	attackSpacing1 = 0;
	attackSpacing2 = 0;
	attackSpacing3 = 0;

	leftMx = 0; 
	leftMy = 0;
	lslope = 0;

	defendArm = NULL;

	defendActive = false;
	defendSegActive = false;
	defendSeg2Active = false;
	defendArmTimer = 0;

	defendSpacing1 = 0;
	defendSpacing2 = 0;
	defendSpacing3 = 0;

	rightMx = 0;
	rightMy = 0;
	rslope = 0;

	radAngle = 0;


	balls.addMetaball(new Metaball2D(px,py,50.0));//body of amoeba
}
