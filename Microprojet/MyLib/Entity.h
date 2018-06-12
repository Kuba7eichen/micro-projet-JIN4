#pragma once
#include <chrono>

class Entity
{
public:
	Entity(double x, double y);
	virtual void update(double elapsed) = 0;
	
	

protected:
	double pos_x;
	double pos_y;

};


