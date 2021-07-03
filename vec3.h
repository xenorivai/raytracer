#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <fstream>

class vec3{
public:
	double x , y , z;
public:
	//default constructor initialises to 0
	vec3() : x(0) , y(0) , z(0) {}

	//paramaterised constructor
	vec3(double X , double Y , double Z) : x(X) , y(Y) , z(Z){}

	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }

	vec3 operator-() const{
		return vec3(-x , -y , -z);
	}

	vec3& operator+= (const vec3 *v){
		x += v->x;
		y += v->y;
		z += v->z;

		return *this;
	}

	vec3 &operator*=(const double t) {
		x *= t;
		y *= t;
		z *= t;

		return *this;
	}

	vec3& operator/=(const double t){
		return (*this) *= 1/t;
	}

	double length() const{
		return std::sqrt(x*x + y*y + z*z);
	}
	double length_sq() const{
		return (x*x + y*y + z*z);
	}

	inline static vec3 random(void){
		return vec3(random_double() , random_double() , random_double());
	}

	inline static vec3 random(double min , double max){
		return vec3(random_double(min,max) , random_double(min,max) , random_double(min,max));
	}

	bool near_zero(void) const{
		const auto s = 1e-8;
		return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
	}

};

inline std::ostream& operator<<(std::ostream &out , const vec3 &v){
	return out << v.x << ' ' << v.y << ' ' << v.z ;
}

inline vec3 operator+(const vec3 &u , const vec3 &v){
	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3 &u, const vec3 &v){
	return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline vec3 operator*(const vec3 &u, const vec3 &v){
	return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec3 operator*(const vec3 &v , double t){
	return vec3(v.x * t , v.y * t , v.z * t);
}

inline vec3 operator*(double t , const vec3 &v ){
	return v * t;
}

inline vec3 operator/(const vec3 &v , double t){
	return v * (1/t) ;
}

inline double dot(const vec3 &u , const vec3 &v){
	return u.x * v.x + u.y * v.y + u.z * v.z ;
}

inline vec3 cross(const vec3 &u , const vec3 &v){
	return vec3(u.y*v.z - v.y*u.z , v.x*u.z - u.x*v.z , u.x*v.y - v.x*u.y);
}

inline vec3 unit_vector(const vec3 &v){
	return v / v.length();
}

vec3 random_in_unit_sphere(void){
	while(true){
		vec3 p = vec3 :: random(-1,1);
		if(p.length_sq() >= 1) continue;
		else return p;
	}
}

vec3 random_unit_vector(){
	return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere (const vec3 &normal) {
	vec3 in_unit_sphere = random_in_unit_sphere();
	if(dot(in_unit_sphere , normal) > 0.0) return in_unit_sphere;
	else return -in_unit_sphere;
}

using point3 = vec3;
using color = vec3;

#endif
