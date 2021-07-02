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
	camera(){
		const auto aspect_ratio = 16.0 / 9.0;
		
		/* Viewport : Through which rays are passed */
		auto view_H = 2.0; // viewport height
		auto view_W = aspect_ratio * view_H; // viewport width
		auto focal_length = 1.0; // distance b/w projection plane and projection point
		origin = point3(0,0,0);
		horizontal = vec3(view_W, 0.0 , 0.0);
		vertical = point3(0.0,view_H,0.0);
		lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);
	}

	ray get_ray(double u , double v) const{
		return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
	}
};

#endif