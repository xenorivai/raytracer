#ifndef MATERIAL_H
#define MATERIAL_H

#include "raytracer.h"
struct hit_record;

class material{
public:
	virtual bool scatter(const ray &ray_in , const struct hit_record &rec , color &scattered_color , ray &scattered) const = 0;
};

//class of materials performing lambertian reflection
class lambertian : public material {
public:
	color _color;	//self color
public:
	lambertian(const color &a) : _color(a) {}

	virtual bool scatter(const ray &ray_in , const struct hit_record &rec , color &scattered_color , ray &scattered) const override{

		auto scatter_direction = rec.normal + random_unit_vector();
		
		if(scatter_direction.near_zero()) scatter_direction = rec.normal;

		scattered = ray(rec.p , scatter_direction);//scattered ray is, any random ray with origin as point of intersection
		scattered_color = _color;
		
		return true;
	}
};


//class of materials performing specular reflection 
class metal : public material {
public:
	color _color;//self color
	double fuzz;
public:
	metal(const color &a, double f = 0) : _color(a),fuzz(f){}

	virtual bool scatter(const ray &ray_in , const struct hit_record &rec , color &scattered_color , ray &scattered) const override {

		vec3 reflected_direction = reflect(unit_vector(ray_in.direction()) , rec.normal);

		scattered = ray(rec.p , reflected_direction + fuzz*random_in_unit_sphere());//for metals, scattered ray is reflected ray
		scattered_color = _color;

		return (dot(scattered.direction(), rec.normal) > 0);//successfull scatter iff reflected ray goes outwards 
	}
};

//refractive materials
class dielectric : public material{
public:
	double ri;
private:
	static double probability_of_reflection(double cos_theta , double ri){
		//Schlick's approximation for prob of reflection
		double r0 = (1-ri)/(1+ri);
		r0 = r0*r0;
		return r0 + (1-r0)*pow((1-cos_theta),5);
	}
public:
	dielectric(double idx) : ri(idx){}

	virtual bool scatter(const ray &ray_in , const hit_record &rec , color &scattered_color , ray &scattered) const override{

		scattered_color = color(1,1,1);

		double ratio = rec.front_face? (1/ri) : ri;

		vec3 incident_unit_vector = unit_vector(ray_in.direction());
		double cos_theta = fmin(dot(incident_unit_vector,rec.normal),1.0);
		double sin_theta = sqrt(1-cos_theta*cos_theta);

		bool cannot_reflect = ratio * sin_theta > 1;

		vec3 refracted_direction;
		if(cannot_reflect || probability_of_reflection(cos_theta,ri) > random_double() ){
			refracted_direction = reflect(incident_unit_vector,rec.normal);
		}
		else{
			refracted_direction = refract(incident_unit_vector,rec.normal,ratio);
		}

		scattered = ray(rec.p, refracted_direction);
		return true;
	}
};

#endif