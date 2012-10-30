#ifndef METABALL2D_H_
#define METABALL2D_H_

class Metaball2D
{
	

public:

	Metaball2D(double px , double py , double radius, bool normal)
	{
		this->px = px;
		this->py = py;
		this->radius = radius;
		radiusSquared = radius * radius;
		this->normal = normal;
	}

	inline double Equation(float x, float y) 
	{ 
		if(normal)
		{
			double denom =sqrt((x -px)*(x-px) + (y-py)*(y-py));
			if( denom == 0)
				return 1000.0;
			return (radius/denom);
		}
		else
		{
			//R / ( |x-x0| + |y-y0| ) 
			double denom =  abs((x -px)) + abs((y-py));
			if( denom == 0)
				return 1000.0;
			return (radius/denom);
		}
	}

	void move(double x, double y)
	{
		px = x;
		py = y;
	}

	void shift(double x, double y)
	{
		px += x;
		py += y;
	}
	
	inline double getRadius()
	{
		return radius;
	}
	
	inline double getPx()
	{
		return px;
	}

	inline double getPy()
	{
		return py;
	}

private:
	
	double px,py;//point x and y
	double radius;
	double radiusSquared;
	bool normal;
};

#endif