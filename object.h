/*
	Container class for abstract hittable object
*/

#ifndef OBJECT_H
#define OBJECT_H


#include"ray.h"


//holds information of point of intersection , normal at pt of intersection , and distance from ray's origin(t)
struct hit_record{
	point3 p;
	vec3 normal;
	double t;
	bool front_face;


	inline void set_face_normal(const ray &r , const vec3 &out_normal){
		//front_face is true if ray is outside sphere false otherwise
		front_face = dot(r.direction(),out_normal);
		normal = front_face ? out_normal : -out_normal;
	}
};

class object{
public :
	virtual bool hit(const ray& r , double t_min , double t_max , hit_record& record) const{return false;}
};

#endif