#include"Amoeba.h"

Amoeba::Amoeba(){
	velX = 0;
	velY = 0;

	balls.addMetaball(new Metaball2D(0.0,0.0,4.0));
	balls.addMetaball(new Metaball2D(1.0,5.0,2.0));
	balls.addMetaball(new Metaball2D(-5.0,4.0,1.0));
	balls.addMetaball(new Metaball2D(-5.0,-5.0,1.0));
	balls.addMetaball(new Metaball2D(6.0,-1.0,1.0));

}

