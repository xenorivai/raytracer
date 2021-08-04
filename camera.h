#ifndef CAMERA_H
#define CAMERA_H

#include "raytracer.h"

class camera{
private:
	point3 origin; // eye
	point3 lower_left_corner;
	vec3 horizontal;// unit vector along X-axis
	vec3 vertical;// unit vector along Y-axis

public:
	camera(point3 lf , point3 la , vec3 vup , double vfov , double aspect_ratio){
		double theta = degrees_to_radians(vfov);
		double h = std::tan(theta/2);
		
		
		/* Viewport : Through which rays are passed */
		auto view_H = 2.0*h; // viewport height
		auto view_W = aspect_ratio * view_H; // viewport width
		
		/*Orthogonal Basis for camera movement*/
		vec3 w = unit_vector(lf-la);//lookfrom-lookat axis
		vec3 u = unit_vector(cross(vup,w));
		vec3 v = cross(w,u);		
		
		origin = lf;
		horizontal = view_W * u;
		vertical = view_H * v;
		lower_left_corner = origin - horizontal/2 - vertical/2 - w;
	}

	ray get_ray(double x , double y) const{
		return ray(origin, lower_left_corner + x*horizontal + y*vertical - origin);
	}
};

#endif