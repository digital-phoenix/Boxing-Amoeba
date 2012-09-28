
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

	void move()
	{
		px = rand()%1000;
		py = rand()%1000;
	}
	
	
private:
	
	
	double radius;
};

