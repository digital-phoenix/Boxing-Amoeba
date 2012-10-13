#include"Amoeba.h"

Amoeba::Amoeba(){
	velX = 0;
	velY = 0;

	balls.addMetaball(new Metaball2D(0.0,0.0,15.0));
	balls.addMetaball(new Metaball2D(1.0,5.0,25.0));
	balls.addMetaball(new Metaball2D(-20.0,4.0,22.0));
	balls.addMetaball(new Metaball2D(-15.0,-5.0,12.0));
	balls.addMetaball(new Metaball2D(6.0,-1.0,30.0));

}

