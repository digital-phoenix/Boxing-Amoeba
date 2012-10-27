#include"Amoeba.h"

Amoeba::Amoeba():balls(0.0,0.0,1.0){}

Amoeba::Amoeba(double px, double py, double radius, double scale, bool normal) : balls(0.0,0.0,1.0)
{
velX = 0;
velY = 0;

this->px = px;
this->py = py;
this->radius = radius;
this->normal = normal;
this->scale = scale;
needToResize = false;

identifier = "Amoeba";

attackArm = NULL;

attackActive = false;
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
defendWaitTimer = 0;

defendSpacing1 = 0;
defendSpacing2 = 0;
defendSpacing3 = 0;

rightMx = 0;
rightMy = 0;
rslope = 0;


isCollision = false;
colPx = 0;
    colPy = 0;
colAngle = 0;

canMoveUp = true;
canMoveDown = true;
canMoveLeft = true;
canMoveRight = true;

isBody = false;
isDefend = false;
isAttack = false;
isWall = false;

attackFistPx = 0;
attackFistPy = 0;
attackFistRadius = 0;

defendFistPx = 0;
defendFistPy = 0;
defendFistRadius = 0;

balls.addMetaball(new Metaball2D(px,py,radius));//body of amoeba
}


