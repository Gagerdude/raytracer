#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "../models/Model.h"
#include "../materials/Material.h"
#include "Ray.h"
#include "Camera.h"
#include "../util/ImageWrapper.h"
#include "../models/BVHNode.h"

#include <vector>
#include <string>
#include <functional>
#include <random>
#include <mutex>
#include <queue>

class Raytracer{
    public:
        Raytracer();

        ImageWrapper<double> render(const Camera& camera, Model** Model_array, int num_Models, int resolution_x, int resolution_y, int num_samples, int max_reflections, int num_threads) const;

        static thread_local std::mt19937 rng;

    private:
        static thread_local std::random_device rd;
        
        void render_block(ImageWrapper<double>& img, const Camera& camera, BVHNode* scene, int x_start, int x_end, int y_start, int y_end, int num_samples, int max_reflections) const;

        void render_async(std::queue<std::function<void()>>& work_queue, std::mutex& work_queue_mutex) const;

        vec3 color(const Ray& ray, BVHNode* bvh, int ray_depth, int max_ray_depth) const;

        bool hit_list(const Ray& ray, double t_min, double t_max, Model** Model_array, int num_Models, hit_record& rec) const;
};

#endif