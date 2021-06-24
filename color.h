#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

void write_color(std::ofstream &fout , color &pixel_color){
	fout << int(255.999 * pixel_color.x) << ' '
		 << int(255.999 * pixel_color.y) << ' '
		 << int(255.999 * pixel_color.z) << '\n';

	return;
}

#endif