CPP = g++ -std=c++17 -fPIC

CFLAGS = -c -O3 -Wall

OBJS = CheckeredTexture.o ConstantTexture.o

libTextures.so: $(OBJS)
	g++ -shared -o libTextures.so $(OBJS) 

CheckeredTexture.o: CheckeredTexture.h CheckeredTexture.cpp
	$(CPP) $(CFLAGS) CheckeredTexture.cpp

ConstantTexture.o: ConstantTexture.h ConstantTexture.cpp
	$(CPP) $(CFLAGS) ConstantTexture.cpp
	
clean:
	rm *.o *.so