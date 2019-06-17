CPP = g++ -std=c++17 -fPIC

CFLAGS = -c -O3 -Wall $(INCLUDES)

INCLUDES = -Iengine -Imaterials -Imodels -Iutil

DEPS = main.o engine/libEngine.so materials/libMaterials.so models/libModels.so util/libUtil.so

main: $(DEPS)
	g++ -fPIC -o main $(DEPS)

main.o: main.cpp
	$(CPP) $(CFLAGS) main.cpp

engine/libEngine.so:
	(cd engine; make)

materials/libMaterials.so:
	(cd materials; make)

models/libModels.so:
	(cd models; make)

util/libUtil.so:
	(cd util; make)

clean:
	(cd engine; make clean)
	(cd models; make clean)
	(cd materials; make clean)
	(cd util; make clean)
	rm *.o main