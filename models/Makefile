CPP = g++ -std=c++17 -fPIC

CFLAGS = -c -O3 -Wall

OBJS = AxisAlignedBoundingBox.o BVHNode.o moving_sphere.o Sphere.o

libModels.so: $(OBJS)
	g++ -shared -o libModels.so $(OBJS) 

AxisAlignedBoundingBox.o: AxisAlignedBoundingBox.h AxisAlignedBoundingBox.cpp
	$(CPP) $(CFLAGS) AxisAlignedBoundingBox.cpp

BVHNode.o: Model.h BVHNode.h BVHNode.cpp
	$(CPP) $(CFLAGS) BVHNode.cpp
	
moving_sphere.o: Model.h moving_sphere.h moving_sphere.cpp
	$(CPP) $(CFLAGS) moving_sphere.cpp
	
Sphere.o: Model.h Sphere.h Sphere.cpp
	$(CPP) $(CFLAGS) Sphere.cpp
	
clean:
	rm *.o *.so