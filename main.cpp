#include "vec3.h"
#include "color.h"
#include "ray.h"

double sphere_intersect(const point3 &center , double radius , const ray &r){
	//vec from ray origin to center of sphere
	vec3 OC =  r.orig - center;
	double b = dot(r.dir,OC);
	double a = (r.dir.length())*(r.dir.length());
	double c = (OC.length())*(OC.length()) - radius*radius;

	double dis = b*b - a*c;

	//no hit
	if(dis < 0){
		return -1;
	}

	//return closest hit point
	//b > 0 as [ acos(dot(r.dir,OC)/b.length()) < pi/2 ]
	else{
		return (-b - std::sqrt(dis)/ (a) );
	}
}


color ray_color(const ray &r){
	//sphere
	point3 center(0,0,-1);
	double t = sphere_intersect(center , 0.5 , r);
	//if intersect at distance 't' from ray origin
	if(t > 0){
		vec3 N = unit_vector(r.at(t) - center);//Normal at point of intersection
		return color(0.5*(N.x + 1.0),0.5*(N.y + 0.25),0.5*(N.z + 0.75));
	}

	//linearly interpolated blended background
	/*	Gives color to a ray endpoint on projection plane relative to its height , produces 
		linear gradient along y-axis.
	*/
	vec3 unit_dir = unit_vector(r.direction());
	double p = 0.5*(unit_dir.getY() + 1.0);
	return (1.0 - p)*color(0,0,0) + p*color(0.964,0.69,0.69);//0.50588235294
	
	//black bg
	// return (1.0 - p)*color(0,0,0) + p*color(0.5,0.5,0.5);
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
            color pixel_color = ray_color(r);
            write_color(fout, pixel_color);
        }
    }
	fout.close();
	std :: cerr <<"\nDone\n";

	return 0;
}
