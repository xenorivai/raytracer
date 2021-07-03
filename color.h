#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

void write_color(std::ofstream &fout , color &pixel_color , int samples_per_pixel){


	/*	
		- samples_per_pixel = sampling rate (Hz) 
		- for each pixel #samples_per_pixel rays are passed through that pixel
		- then color for each sample is averaged into a single color
		- This effectively is supersample antialiasing
	*/
	double r = pixel_color.x;
	double g = pixel_color.y;
	double b = pixel_color.z;
	

	/*
		instead of adding fractional contribution of each sample each time a ray is passed through the pixel, 
		just add the resultant full color due to each sample , 
		and then divide at the end by the number of samples when writing out the color
	*/

	//gamma correction with gamma = 2
	r = sqrt(r / samples_per_pixel);
	g = sqrt(g / samples_per_pixel);
	b = sqrt(b / samples_per_pixel);

	fout << int(255.999 * clamp(r,0.0,0.999)) << ' '
		 << int(255.999 * clamp(g,0.0,0.999)) << ' '
		 << int(255.999 * clamp(b,0.0,0.999)) << '\n';

	return;
}

#endif