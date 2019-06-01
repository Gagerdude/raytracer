#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "model.h"
#include "Ray.h"

#include <vector>
#include <string>

class Raytracer{
    public:
        Raytracer();

        void setResolution(int w, int h);
        void setNumSamplesPerPixel(int samples);
        void setModels(model** model_array, int array_size);

        void render(std::string filename) const;

    private:
        int width, height, num_samples;

        model** models;
        int num_models;

        vec3 color(const Ray& ray) const;

        bool hit_list(const Ray& ray, float t_min, float t_max, hit_record& rec) const;
};

#endif