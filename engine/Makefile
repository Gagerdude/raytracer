CPP = g++ -std=c++17 -fPIC

CFLAGS = -c -O3 -Wall

OBJS = Camera.o Ray.o Raytracer.o vec3.o

libEngine.so: $(OBJS)
	g++ -shared -o libEngine.so $(OBJS) 

Camera.o: Camera.h Camera.cpp
	$(CPP) $(CFLAGS) Camera.cpp

Ray.o: Ray.h Ray.cpp
	$(CPP) $(CFLAGS) Ray.cpp
	
Raytracer.o: Raytracer.h Raytracer.cpp
	$(CPP) $(CFLAGS) Raytracer.cpp
	
vec3.o: vec3.h vec3.cpp
	$(CPP) $(CFLAGS) vec3.cpp
	
clean:
	rm *.o *.so