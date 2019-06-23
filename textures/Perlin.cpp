#include "Perlin.h"

#include "Raytracer.h"

#include <random>

double perlin_interpolate(vec3 c[2][2][2], double u, double v, double w){
    double sum = 0;
    
    double uu = u * u * (3 - (2 * u));
    double vv = v * v * (3 - (2 * v));
    double ww = w * w * (3 - (2 * w));

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                vec3 weight_vec(u-i, v-j, w-k);
                sum += (i*uu + (1 - i) * (1 - uu)) *
                       (j*vv + (1 - j) * (1 - vv)) *
                       (k*ww + (1 - k) * (1 - ww)) *
                       dot(c[i][j][k], weight_vec);
            }
        }
    }

    return sum;
}

Perlin::Perlin(){
    ranvec = perlin_generate();
    perm_x = perlin_generate_permutation();
    perm_y = perlin_generate_permutation();
    perm_z = perlin_generate_permutation();
}

Perlin::~Perlin(){
    delete[] ranvec;
    delete[] perm_x;
    delete[] perm_y;
    delete[] perm_z;
}

double Perlin::noise(const vec3& p) const{
    double u = p.x() - std::floor(p.x());
    double v = p.y() - std::floor(p.y());
    double w = p.z() - std::floor(p.z());

    int i = std::floor(p.x());
    int j = std::floor(p.y());
    int k = std::floor(p.z());

    vec3 c[2][2][2];

    for(int di = 0; di < 2; di++){
        for(int dj = 0; dj < 2; dj++){
            for(int dk = 0; dk < 2; dk++){
                c[di][dj][dk] = ranvec[perm_x[(i+di) & 255] ^ perm_y[(j+dj) & 255] ^ perm_z[(k+dk) & 255]];
            }
        }
    }

    return perlin_interpolate(c, u, v, w);
}

double Perlin::turbulence(vec3 p, int depth) const{
    double sum = 0;
    double weight = 1;

    for(int i = 0; i < depth; i++){
        sum += weight * noise(p);
        weight *= .5;
        p *= 2;
    }

    return std::abs(sum);
}

vec3* Perlin::perlin_generate(){
    vec3* rand_array = new vec3[256];

    for(int i = 0; i < 256; i++){
        rand_array[i] = vec3::random();
    }

    return rand_array;
}

void Perlin::permute(int* array, int array_size){
    std::uniform_real_distribution<double> dist(0, 1);

    for(int i = array_size - 1; i > 0; i--){
        int rand_index = int(dist(Raytracer::rng) * (i + 1));
        std::swap(array[rand_index], array[i]);
    }
}

int* Perlin::perlin_generate_permutation(){
    int* array = new int[256];

    for(int i = 0; i < 256; i++){
        array[i] = i;
    }

    permute(array, 256);
    
    return array;
}
