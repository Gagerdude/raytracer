#include "Perlin.h"

#include "Raytracer.h"

#include <random>

double Perlin::noise(const vec3& p) const{
    int i = int(4 * p.x()) & 255;
    int j = int(4 * p.y()) & 255;
    int k = int(4 * p.z()) & 255;

    return randouble[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
}

static double* perlin_generate(){
    double* rand_array = new double[256];
    std::uniform_real_distribution<double> dist(0, 1);

    for(int i = 0; i < 256; i++){
        rand_array[i] = dist(Raytracer::rng);
    }

    return rand_array;
}

void permute(int* array, int array_size){
    std::uniform_real_distribution<double> dist(0, 1);

    for(int i = array_size - 1; i > 0; i--){
        int rand_index = int(dist(Raytracer::rng) * (i + 1));
        std::swap(array[rand_index], array[i]);
    }
}

static int* perlin_generate_permutation(){
    int* array = new int[256];

    for(int i = 0; i < 256; i++){
        array[i] = i;
    }

    permute(array, 256);
    
    return array;
}

double* Perlin::randouble = perlin_generate();
int* Perlin::perm_x = perlin_generate_permutation();
int* Perlin::perm_y = perlin_generate_permutation();
int* Perlin::perm_z = perlin_generate_permutation();