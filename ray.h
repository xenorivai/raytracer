#ifndef RAY_H
#define RAY_H

#include"vec3.h"

class ray{
	
public:
	point3 orig;
	vec3 dir;

public:
    //default constructor
    ray() {}
    ray(const point3 &origin , const vec3 &direction) 
		: orig(origin) , dir(direction)
	{}

	point3 origin() const  { return orig; }
	vec3 direction() const { return dir; }

	//coordinates of a point at distance 't' from origin
	point3 at(double t) const{
		return orig + t*dir;
	}
};

#endif