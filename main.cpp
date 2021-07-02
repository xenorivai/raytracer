#include "raytracer.h"
#include "color.h"
#include "sphere.h"
#include "object_list.h"
#include "camera.h"

color ray_color(const ray &r, const object_list &world){

	hit_record temp_record;

	//if ray r hits 'any' object in world, store info in hit_record record
	if(world.hit(r , 0 , infinity , temp_record)){
		return 0.5*(temp_record.normal + color(1,0.2,0.5));
	}

	//linearly interpolated blended background
	/*	Gives color to a ray endpoint(pixel) on projection plane relative to its height,
		darker pixels at bottom , 
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
	const int samples_per_pixel = 100;

	//World
	object_list world;
	world.add(make_shared<sphere>(point3(0,0,-1), 0.5));//sphere object
	world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));//sphere object
	//Image has small sphere above big sphere because small spehere closer than big sphere


	//Camera
	camera cam;

	//Render to out.ppm
	std:: ofstream fout;
	fout.open("./out.ppm");

	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int i = image_height-1; i >= 0; i--) {
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < image_width; j++) {
            color pixel_color = color(0,0,0);
			for(int s = 0 ; s < samples_per_pixel; s++){
				auto u = double(j + random_double()) / (image_width-1);
        	    auto v = double(i + random_double()) / (image_height-1);

				ray r = cam.get_ray(u,v);
				pixel_color = pixel_color + ray_color(r,world);
			}
            write_color(fout, pixel_color , samples_per_pixel);
        }
    }
	fout.close();
	std :: cerr <<"\nDone\n";

	return 0;
}
