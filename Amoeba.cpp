#include"Amoeba.h"

Amoeba::Amoeba()
{
	velX = 0;
	velY = 0;

	px = 10;
	py = 100;

	armBall = NULL;
	armTimer = 0.0;
	armActive = false;
	segActive = false;
	seg2Active = false;

	balls.addMetaball(new Metaball2D(px,py,50.0));//body of amoeba
	Metaball2DGroup *group = new Metaball2DGroup();
	//group->addMetaball(new Metaball2D(250.0, 250.0, 10.0)); 
	//balls.addSubgroup(group);
}

