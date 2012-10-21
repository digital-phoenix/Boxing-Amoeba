#include"Amoeba.h"

Amoeba::Amoeba()
{
	velX = 0;
	velY = 0;

	px = 100;
	py = 100;

	armBall = NULL;
	armTimer = 0.0;
	armActive = false;
	segActive = false;
	seg2Active = false;

	balls.addMetaball(new Metaball2D(px,py,50.0));//body of amoeba
}
