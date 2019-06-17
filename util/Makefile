CPP = g++ -std=c++17 -fPIC

CFLAGS = -c -O3 -Wall

OBJS = PNGWriter.o

libUtil.so: $(OBJS)
	g++ -shared -o libUtil.so $(OBJS) -lpng

PNGWriter.o: PNGWriter.h PNGWriter.cpp
	$(CPP) $(CFLAGS) PNGWriter.cpp
	
clean:
	rm *.o *.so