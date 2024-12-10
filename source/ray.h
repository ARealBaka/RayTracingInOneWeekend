#ifndef RAY_H
#define RAY_H
#include"vec3.h"
class ray
{

public:
	ray(){}
	ray(const point3& origin,const vec3& direction):ori(origin),dir(direction){}

	const point3& origin() const{ return ori; }
	const vec3& direction() const{ return dir; }

	point3 at(double t) const
	{
		return ori + dir * t;
	}


private:
	point3 ori;
	vec3 dir;
};

#endif // !RAY_H

