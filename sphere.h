#ifndef SPHERE_H
#define SPHERE_H

#include"object.h"
#include"vec3.h"

class sphere : public object{
public:
	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;
public:
	sphere(){}
	sphere(point3 c , double r , shared_ptr<material> m) : center(c) , radius(r) , mat_ptr(m){}

	virtual bool hit(const ray& r , double t_min , double t_max , hit_record& record) const;
};

bool sphere :: hit(const ray& r , double t_min , double t_max , hit_record& record) const{
	//vec from ray origin to center of sphere
	vec3 OC =  r.orig - center;
	double b = dot(r.dir,OC);
	double a = (r.dir.length())*(r.dir.length());
	double c = (OC.length())*(OC.length()) - radius*radius;

	double dis = b*b - a*c;

	//no hit
	if(dis < 0){ return false; }

	//return closest hit point
	//b > 0 as [ acos(dot(r.dir,OC)/b.length()) < pi/2 ]
	double root = (-b - std::sqrt(dis))/ (a);

	if(root < t_min || root > t_max){
		root = (-b + std::sqrt(dis))/ (a); //try other root
		if(root < t_min || root > t_max) return false;	//does not hit exit
	}

	//update record values
	record.t = root;//distance
	record.p = r.at(root);//point of intersection
	vec3 out_normal = (record.p - center) / radius; // unit outward normal vector 
	record.set_face_normal(r,out_normal);
	record.mat_ptr = mat_ptr;

	return true;
}

#endif