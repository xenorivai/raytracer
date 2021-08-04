#include "raytracer.h"
#include "color.h"
#include "camera.h"
#include "object_list.h"
#include "sphere.h"
#include "material.h"
#include <vector>
#include <iostream>


color ray_color(const ray& r, const object_list* world, int depth) {

	hit_record temp_record;

	if (depth <= 0) return color(0, 0, 0);

	//if ray r hits 'any' object in world,store info in temp_record which is a hit_record
	if (world->hit(r, 0.001, infinity, temp_record)) {

		ray scattered;//after hitting 'any' object the scattered ray
		color scattered_color;
		if (temp_record.mat_ptr->scatter(r, temp_record, scattered_color, scattered)) {
			return scattered_color * ray_color(scattered, world, depth - 1);
		}
		else return color(0, 0, 0);
	}

	//linearly interpolated blended background
	/*	Gives color to a ray endpoint(pixel) on projection plane relative to its height,
		darker pixels at bottom
	*/
	vec3 unit_dir = unit_vector(r.direction());
	double p = 0.5 * (unit_dir.getY() + 1.0);
	return (1.0 - p) * color(0, 0, 0) + p * color(0.7, 0.7, 0.7);
}


object_list* create(){
	object_list* world = new object_list;

	auto _ground = make_shared<dielectric>(1.8);
	world->add(make_shared<sphere>(point3(0,-1000,0),1000,_ground));

	auto material1 = make_shared<dielectric>(1.5);
    world->add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.0, 0.1));
    world->add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.1, 0.2, 0.7), 0.1);
    world->add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
	
	world->add(make_shared<sphere>(point3(-2, 1, -1), 1.0, material3));
	world->add(make_shared<sphere>(point3(-1, 1, -1), 0.6, material3));

	auto _random_lambert = make_shared<lambertian>(color(random_double(0,1),random_double(0,1),random_double(0,1)));
	auto _random_metal = make_shared<metal>(color(random_double(0,1),random_double(0,1),random_double(0,1)),random_double(0,1));
	auto _random_glass = make_shared<dielectric>(random_double(0.1,5.0));

	std::vector<shared_ptr<material>> mat_list;
	mat_list.emplace_back(_random_glass);
	mat_list.emplace_back(_random_metal);
	mat_list.emplace_back(_random_lambert);

	for(int i = 0 ; i < 10 ; i++ ){
		world->add(make_shared<sphere>(point3(random_double(1.2,2.8),0.2,random_double(1.2,2.2)),0.2,mat_list[int(random_double())%3]));
		world->add(make_shared<sphere>(point3(random_double(-2.8,-1.2),0.2,random_double(-2.8,-1.2)),0.2,mat_list[int(random_double())%3]));
	}

	return world;
}


void render(camera &cam, const double aspect_ratio , const int image_width , const int samples_per_pixel , const int max_depth){

	object_list* world = create();

	const int image_height = int(image_width / aspect_ratio);
	const char* path = "./out.ppm";
	std::ofstream fout(path);

	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int i = image_height - 1; i >= 0; i--) {
		std::cerr << "\rRemaining : " << i << ' ' << std::flush;
		for (int j = 0; j < image_width; j++) {
			color pixel_color = color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++) {
				/*
					- for each sample pick a random spot on the pixel and pass ray through it
					- then add color for that sample to pixel color
					- in write_color() average out the effect of multisampling by dividing by samples_per_pixel
				*/
				auto u = double(j + random_double()) / (image_width - 1);
				auto v = double(i - random_double()) / (image_height - 1);

				ray r = cam.get_ray(u, v);
				pixel_color = pixel_color + ray_color(r, world, max_depth);
			}
			write_color(fout, pixel_color, samples_per_pixel);
		}
	}
	fout.close();
	std::cerr << "\nDone\n";
}

int main() {

	//Image properties
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 1024;
	const int image_height = int(image_width / aspect_ratio);
	const int samples_per_pixel = 500;
	const int max_depth = 100; //recursion depth for ray_color(), also bounce limit for each ray	

	//Camera
	vec3 vup(0,1,0);
	point3 lookfrom(5,3,4);
	point3 lookat(0,0,0);
	double vfov = 60;

	camera cam(lookfrom , lookat , vup , vfov , aspect_ratio);

	//Render to out.ppm
	render(cam,aspect_ratio,image_width,samples_per_pixel,max_depth);

	return 0;
}