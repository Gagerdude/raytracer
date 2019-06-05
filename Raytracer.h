#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "model.h"
#include "Ray.h"

#include <vector>
#include <string>
#include <functional>
#include <random>

class Raytracer{
    public:
        Raytracer();

        void render(std::string filename, model** model_array, int num_models, int resolution_x, int resolution_y, int num_samples, int max_reflections) const;

    private:
        std::mt19937 generator;
        std::uniform_real_distribution<float> rand_dist;
        std::function<float()> rng;

        vec3 color(const Ray& ray, model** model_array, int num_models, int ray_depth, int max_ray_depth) const;

        bool hit_list(const Ray& ray, float t_min, float t_max, model** model_array, int num_models, hit_record& rec) const;
};

#endif