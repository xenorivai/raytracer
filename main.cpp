#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"

color ray_color(const ray &r, sphere &s , hit_record &record){

	//sphere-intersection
	if(s.hit(r,0.0,1.0,record)){
		return color(0.5*(record.normal.x + 1.0),0.15*(record.normal.y + 0.75),0.45*(record.normal.z + 0.75));
	}

	//linearly interpolated blended background
	/*	Gives color to a ray endpoint on projection plane relative to its height , produces 
		linear gradient along y-axis.
	*/
	vec3 unit_dir = unit_vector(r.direction());
	double p = 0.5*(unit_dir.getY() + 1.0);
	return (1.0 - p)*color(0,0,0) + p*color(0.964,0.69,0.50588235294); // linear gradient from complete black to some color
	
	//black bg
	// return (1.0 - p)*color(0,0,0) + p*color(0.5,0.5,0.5); // kinda grayscale bg
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
	point3 origin(0,0,0); // eye
	vec3 horizontal(view_W , 0 , 0); // unt vector along X-axis
	vec3 vertical(0,view_H,0); // unt vector along Y-axis
	point3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);
	


	//sphere-1
	sphere s(point3(-0.5,0.5,-1),0.15);
	hit_record sphere_record;

	//sphere-2
	// sphere c(point3(0.5,0.5,-1),0.15);
	// hit_record sphere_recordC;

	//Render to out.ppm
	std:: ofstream fout;
	fout.open("./out.ppm");

	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int i = image_height-1; i >= 0; i--) {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {
            auto u = double(j) / (image_width-1);
            auto v = double(i) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r , s , sphere_record);
			// color pixel_colorC = ray_color(r , c , sphere_recordC);//second sphere
            write_color(fout, pixel_color);
			// write_color(fout, pixel_colorC);//second sphere
        }
    }
	fout.close();
	std :: cerr <<"\nDone\n";

	return 0;
}
