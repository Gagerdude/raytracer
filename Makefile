CPP = g++ -std=c++17 -fPIC

CFLAGS = -c -O3 -Wall $(INCLUDES)

SHARED_OBJS = \
	engine/libEngine.so\
	materials/libMaterials.so\
	models/libModels.so\
	textures/libTextures.so\
	util/libUtil.so


main: main.o $(SHARED_OBJS)
	g++ -fPIC -o main main.o $(SHARED_OBJS)

main.o: main.cpp
	$(CPP) $(CFLAGS) main.cpp

engine/libEngine.so: engine/*.h engine/*.cpp
	(cd engine; make)

materials/libMaterials.so: materials/*.h materials/*.cpp
	(cd materials; make)

models/libModels.so: models/*.h models/*.cpp
	(cd models; make)

textures/libTextures.so: textures/*.h textures/*.cpp
	(cd textures; make)

util/libUtil.so: util/*.h util/*.cpp
	(cd util; make)

clean:
	(cd engine; make clean)
	(cd models; make clean)
	(cd materials; make clean)
	(cd textures; make clean)
	(cd util; make clean)
	rm *.o main