CPP = g++ -std=c++17 -fPIC

CFLAGS = -c -O3 -Wall

OBJS = Dielectric.o Lambertian.o Metal.o

libMaterials.so: $(OBJS)
	g++ -shared -o libMaterials.so $(OBJS) 

Dielectric.o: Dielectric.h Dielectric.cpp
	$(CPP) $(CFLAGS) Dielectric.cpp

Lambertian.o: Lambertian.h Lambertian.cpp
	$(CPP) $(CFLAGS) Lambertian.cpp
	
Metal.o: Metal.h Metal.cpp
	$(CPP) $(CFLAGS) Metal.cpp
	
clean:
	rm *.o *.so