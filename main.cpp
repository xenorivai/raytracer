#include "raytracer.h"
#include "color.h"
#include "camera.h"
#include "object_list.h"
#include "sphere.h"
#include "material.h"
#include <iostream>


color ray_color(const ray &r, const object_list &world , int depth){

	hit_record temp_record;
	
	if(depth <= 0) return color(0,0,0);

	//if ray r hits 'any' object in world,store info in temp_record which is a hit_record
	if(world.hit(r , 0.001 , infinity , temp_record)){

		ray scattered;//after hitting 'any' object the scattered ray
		color scattered_color;
		if(temp_record.mat_ptr->scatter(r,temp_record,scattered_color,scattered)){
			return scattered_color * ray_color(scattered,world,depth-1);
		}
		else return color(0,0,0);
	}

	//linearly interpolated blended background
	/*	Gives color to a ray endpoint(pixel) on projection plane relative to its height,
		darker pixels at bottom
	*/
	vec3 unit_dir = unit_vector(r.direction());
	double p = 0.5*(unit_dir.getY() + 1.0);	
	return (1.0 - p)*color(0,0,0) + p*color(0.5,0.5,0.5); 
}


int main(){

	//Image properties
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 800;
	const int image_height = int(image_width/aspect_ratio);
	const int samples_per_pixel = 200;
	const int max_depth = 400; //recursion depth for ray_color(), also bounce limit for each ray

	//World
	object_list world;
	//Image has small spheres above big sphere because small spehere closer than big sphere

	// auto _ground = make_shared<lambertian>(color(0.8,0.4,0.1));
	// auto _ground = make_shared<dielectric>(1.5);
	// auto _center = make_shared<metal>(color(0.7, 0.1, 0.1));
    // // auto _left   = make_shared<metal>(color(0.8, 0.8, 0.8));
	// auto _left   = make_shared<dielectric>(1.5);
    // auto _right  = make_shared<metal>(color(0.1, 0.1, 0.7));

	auto _ground = make_shared<dielectric>(1.5);
	auto _center = make_shared<dielectric>(1.5);
	auto _left   = make_shared<dielectric>(1.5);
	auto _right  = make_shared<metal>(color(0.8, 0.1, 0.5), 0.9);

	world.add(make_shared<sphere>(point3(0,-100.5,-1),100.0,_ground));
	world.add(make_shared<sphere>(point3(0,0,-1),0.5,_center));
	world.add(make_shared<sphere>(point3(0,0,-2),0.3,_right));
	world.add(make_shared<sphere>(point3(-1.0,0.5,-1),0.5,_left));
	world.add(make_shared<sphere>(point3(1.0,0.5,-1),0.5,_right));

	//Camera
	camera cam(90,aspect_ratio);

	//Render to out.ppm
	const char *path = "./out.ppm";
	std:: ofstream fout(path);

	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int i = image_height-1; i >= 0; i--) {
		// if(i%5 == 0) std :: cout << "\r -" << std :: flush;
		// else if(i%5 == 1) std :: cout << "\r \\" << std :: flush;
		// else if(i%5 == 2) std :: cout << "\r |" << std :: flush;
		// else if(i%5 == 3) std :: cout << "\r /" << std :: flush;
		// else std :: cout << "\r -" << std :: flush;
		std :: cerr << "\rRemaining : " << i << ' ' << std :: flush;
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