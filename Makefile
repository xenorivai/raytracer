main: main.cpp vec3.h color.h ray.h camera.h material.h
	make clean
	g++ -o main main.cpp && ./main

clean:
	rm -rf *.o
	rm -rf *.ppm
	rm -rf main