CPP = g++ -std=c++17 -fPIC

CFLAGS = -c -O3 -Wall

OBJS = PNGWriter.o

LIBS = -lpng

libUtil.so: $(OBJS)
	g++ -shared -o libUtil.so $(OBJS) $(LIBS)

PNGWriter.o: PNGWriter.h PNGWriter.cpp
	$(CPP) $(CFLAGS) PNGWriter.cpp
	
clean:
	rm *.o *.so