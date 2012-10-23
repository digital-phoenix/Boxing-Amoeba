#ifndef SPRITE_H_
#define SPRITE_H_

#include<iostream>
#include<windows.h>
#include<gl/gl.h>     
#include<gl/glut.h>   

class Sprite
{
	public:
		virtual void draw() = 0;
		virtual bool checkCollision(Sprite*) = 0;
		virtual void collision(Sprite*) = 0;
		virtual void update() = 0;
		virtual double getRadius() = 0;
		virtual double getPx() = 0;
		virtual double getPy() = 0;
		
		
};

#endif