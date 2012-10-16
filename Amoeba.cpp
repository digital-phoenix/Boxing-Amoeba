#include"Amoeba.h"

Amoeba::Amoeba(){
	velX = 0;
	velY = 0;

	balls.addMetaball(new Metaball2D(10.0,100.0,50.0));
	Metaball2DGroup *group = new Metaball2DGroup();
	group->addMetaball(new Metaball2D( 250.0, 250.0, 50.0)); 
	balls.addSubgroup(group);
}

