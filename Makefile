main.o: main.cpp
	g++ -c main.cpp

vec3.o : vec3.h
	g++ -c vec3.h

output: main.o vec3.o
	g++ main.o vec3.o -o app

clean:
	rm -rf *.o
	rm -rf *.ppm
