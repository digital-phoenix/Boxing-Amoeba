#include<iostream>
#include<windows.h>
#include<gl/gl.h>     
#include<gl/glut.h>   

class Sprite{
	public:
		virtual void draw() = 0;
		virtual bool collision(Sprite*) = 0;
		virtual void update() = 0;
};