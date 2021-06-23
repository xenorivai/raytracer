#include "vec3.h"
#include "color.h"
#include "ray.h"

//linearly interpolated blue-white blend
/*
	Gives color to a ray endpoint on projection plane relative to its width , produces 
	linear gradient along y-axis.
*/
color ray_color(const ray &r){
	vec3 unit_dir = unit_vector(r.direction());
	double t = 0.5*(unit_dir.getY() + 1.0);

	return (1.0 - t)*color(1,1,1) + t*color(0.8,0,0);
}


int main(){

	//Image properties
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 1024;
	const int image_height = int(image_width/aspect_ratio);


	//Camera
	/* Viewport : Through which rays are passed */
	auto view_H = 2.0; // viewport height
	auto view_W = aspect_ratio * view_H; // viewport width
	auto focal_length = 1.0; //distance b/w projection plane and projection point

	//Ray stuff
	auto origin = point3(0,0,0); // eye
	auto horizontal = vec3(view_W , 0 , 0); // unt vector along X-axis
	auto vertical = vec3(0,view_H,0); // unt vector along Y-axis
	auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);
	
	//Render to out.ppm
	std:: ofstream fout;
	fout.open("./out.ppm");

	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for(int i = 0 ; i <= image_height ; i++){
		std::cerr << "\rScanlines remaining: " << image_height - i << ' ' <<std::flush;
		for(int j = 0 ; j <= image_width ; j++){
			//get coordinates of current pixel
			auto u = double(j) / (image_width - 1);
			auto v = (double(i) / (image_height - 1) );
			
			//create ray to current pixel having base at origin(eye)
			ray r(origin , lower_left_corner + u*horizontal + v*vertical - origin);
			
			color pixel_color = ray_color(r);
			write_color(fout , pixel_color);
		}
	}
	fout.close();
	std :: cerr <<"\nDone\n";

	return 0;
}
