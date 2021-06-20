#include"vec3.h"
#include"color.h"

int main(){

	const int image_width = 1024;
	const int image_height = 1024;

	std:: ofstream fout;
	fout.open("./out.ppm");

	fout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for(int i = 0 ; i <= image_height ; i++){
		std::cerr << "\rScanlines remaining: " << image_height - i << ' ' <<std::flush;
		for(int j = 0 ; j < image_width ; j++){
			color pixel_color(double(i) / (image_width - 1) , double(j) / (image_height - 1) , 0.314)
			write_color(fout , pixel_color);
		}
	}
	fout.close();
	std :: cerr <<"\nDone.\n";

	return 0;
}
