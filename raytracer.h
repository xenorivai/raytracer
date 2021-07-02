#ifndef RAYTRACER_H
#define RAYTRACER_H

#include<cmath>
#include<limits>
#include<memory>
#include<cstdlib>
#include<random>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double> :: infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degree){
	return degree * pi / 180.0;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double clamp(double x , double min , double max){
	if(x < min) return min;
	if(x > max) return max;
	return x;
}

#include "ray.h"
#include "vec3.h"

#endif