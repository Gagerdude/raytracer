#include "Perlin.h"

#include "Raytracer.h"

#include <random>

double triliniear_interpolate(double c[2][2][2], double u, double v, double w){
    double sum = 0;

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                sum += (i*u + (1 - i) * (1 - u)) *
                       (j*v + (1 - j) * (1 - v)) *
                       (k*w + (1 - k) * (1 - w)) *
                       c[i][j][k];
            }
        }
    }

    return sum;
}

double Perlin::noise(const vec3& p) const{
    int i = std::floor(p.x());
    int j = std::floor(p.y());
    int k = std::floor(p.z());

    double u = p.x() - std::floor(p.x());
    double v = p.y() - std::floor(p.y());
    double w = p.z() - std::floor(p.z());

    double c[2][2][2];

    for(int di = 0; di < 2; di++){
        for(int dj = 0; dj < 2; dj++){
            for(int dk = 0; dk < 2; dk++){
                c[di][dj][dk] = randouble[perm_x[(i+di) & 255] ^ perm_y[(j+dj) & 255] ^ perm_z[(k+dk) & 255]];
            }
        }
    }

    return triliniear_interpolate(c, u, v, w);
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