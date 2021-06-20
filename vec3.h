#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include<iostream>
#include<fstream>

using std::sqrt;

class vec3{
private:
	double x , y , z;
public:
	vec3() : x(0.f), y(0.f) , z(0.f) {}
	vec3(double a , double b , double c) : x(a) , y(b) , z(c){}

	vec3 operator -  (void) const{return vec3(-(this->x) , -(this->y) , -(this->z));}

	vec3& operator += (const vec3 &v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return *this;
	}

	vec3& operator *= (const double t){
		this->x *= t;
		this->y *= t;
		this->z *= t;

		return *this;
	}

	vec3& operator /= (const double t){
		return *this *= (1/t);
	}

	double length(void) const{
		return sqrt(x*x + y*y + z*z);
	}

	inline std::ostream& operator<<(std::ostream& out , const vec3 &v){
		return out << v.x << ' ' << v.y << ' ' << v.z;
	}

	inline vec3 operator+ (const vec3 &u , const vec3 &v){
		return vec3(u.x + v.x , u.y + v.y ; u.z + v.z);
	}

	inline vec3 operator- (const vec3 &u , const vec3 &v){
		return vec3(u.x - v.x , u.y - v.y ; u.z - v.z);
	}

	inline vec3 operator* (double t , const vec3 &v){
		return vec3(t * v.x , t * v.y , t * v.z);
	}

	inline vec3 operator* (const vec3 &v , double t){
		return t * v;
	}

	inline vec3 operator/ (vec3 &v, double t) {
    	return (1/t) * v;
	}

	inline double dot (const vec3 &u , const vec3& v){
		return (u.x*v.x + u.y*v.y + u.z*v.z);
	}

	inline vec3 cross (const vec3 &u , const vec3& v){
		return vec3(u.y*v.z - v.y*u.z , v.x*u.z - u.x*v.z , u.x*v.y - v.x*u.y);
	}

	inline vec3 unit_vector(vec3 v){
		return v * (1/v.length());
	}

};

using point3 = vec3;
using color = vec3;

#endif
