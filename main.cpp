#include "raytracer.h"
#include "color.h"
#include "sphere.h"
#include "object_list.h"
#include "camera.h"

color ray_color(const ray &r, const object_list &world , int depth){

	hit_record temp_record;
	
	if(depth <= 0) return color(0,0,0);

	//if ray r hits 'any' object in world, store info in hit_record temp_record
	if(world.hit(r , 0.001 , infinity , temp_record)){
		
		//random target in outside unit_sphere
		point3 target = temp_record.p + temp_record.normal + random_unit_vector(); 
		// point3 target = temp_record.p  + random_in_hemisphere(temp_record.normal); //hemispherical scaterring

		//send new ray towards target from pt of intersection to a random point in the unit sphere
		return 0.5 * ray_color(ray(temp_record.p, target - temp_record.p), world , depth - 1);
	}

	//linearly interpolated blended background
	/*	Gives color to a ray endpoint(pixel) on projection plane relative to its height,
		darker pixels at bottom
	*/
	vec3 unit_dir = unit_vector(r.direction());
	double p = 0.5*(unit_dir.getY() + 1.0);
	return (1.0 - p)*color(0,0,0) + p*color(0.964,0.1,0.1); // linear gradient from complete black to some color
	
	//black bg
	// return (1.0 - p)*color(0,0,0) + p*color(0.5,0.5,0.5); // kinda grayscale bg
}


int main(){

	//Image properties
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 1024;
	const int image_height = int(image_width/aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50; //recursion depth for ray_color()

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
				/*
					- for each sample pick a random spot on the pixel and pass ray through it
					- then add color for that sample to pixel color
					- in write_color() average out the effect of multisampling by dividing by samples_per_pixel				
				*/
				auto u = double(j + random_double()) / (image_width-1);
        	    auto v = double(i - random_double()) / (image_height-1);

				ray r = cam.get_ray(u,v);
				pixel_color = pixel_color + ray_color(r,world,max_depth);
			}
            write_color(fout, pixel_color , samples_per_pixel);
        }
    }
	fout.close();
	std :: cerr <<"\nDone\n";

	return 0;
}