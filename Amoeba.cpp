#include"Amoeba.h"

Amoeba::Amoeba(){
	velX = 0;
	velY = 0;

	balls.addMetaball(new Metaball2D(10.0,100.0,50.0));
	balls.addMetaball(new Metaball2D(20.0, 170.0, 30.0));
}

