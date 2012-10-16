#ifndef METABALL2D_H_
#define METABALL2D_H_

class Metaball2D
{
	

public:

	Metaball2D(double px , double py , double radius)
	{
		this->px = px;
		this->py = py;
		this->radius = radius;
		radiusSquared = radius * radius;
	}

	double Equation(float x, float y) 
	{ 
		int denom = sqrt(((x -px)*(x-px) + (y-py)*(y-py)));
		if( denom == 0)
			return 10000.0;
		return (radius/denom);
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
	
	double px,py;//point x and y
	double radius;
	double radiusSquared;
};

#endif