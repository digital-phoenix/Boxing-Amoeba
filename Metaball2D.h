#ifndef METABALL2D_H_
#define METABALL2D_H_

class Metaball2D
{
	

public:
	double px,py;//point x and y
	Metaball2D(double px , double py , double radius)
	{
		this->px = px;
		this->py = py;
		this->radius = radius;
	}

	float Equation(float x, float y) 
	{ 
		return (radius/sqrt( (x -px)*(x-px) + (y-py)*(y-py)));
	}

	void move(double x, double y)
	{
		px = x;
		py = y;
	}

	void shift(double x, double y){
		px += x;
		py += y;
	}
	
	
private:
	
	
	double radius;
};

#endif