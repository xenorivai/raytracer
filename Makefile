main: main.cpp vec3.h color.h ray.h
	g++ -o main main.cpp && ./main

clean:
	rm -rf *.o
	rm -rf *.ppm
	rm -rf main