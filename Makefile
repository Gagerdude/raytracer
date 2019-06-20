# CPP Compiler Flags
CXXFLAGS = -std=c++17 -g -Wall -O3

# C Preprocessor Flags
CPPFLAGS = -Iengine -Imaterials -Imodels -Itextures -Iutil

# External Libraries
LIBRARIES = -lpng -pthread

# Find all *.o files in this directory, and one directory deep
OBJ_FILES = $(patsubst %.cpp, %.o, $(wildcard *.cpp */*.cpp))

main: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o main $(OBJ_FILES) $(LIBRARIES)

clean:
	rm *.o */*.o main
