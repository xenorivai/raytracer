#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

void write_color(std::ofstream &fout , color &pixel_color , int samples_per_pixel){

	double r = pixel_color.x;
	double g = pixel_color.y;
	double b = pixel_color.z;
	
	double scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	fout << int(255.999 * clamp(r,0.0,0.999)) << ' '
		 << int(255.999 * clamp(g,0.0,0.999)) << ' '
		 << int(255.999 * clamp(b,0.0,0.999)) << '\n';

	return;
}

#endif