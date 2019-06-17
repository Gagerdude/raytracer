#include "Raytracer.h"

#include <limits>
#include <random>

#include <iostream>

thread_local std::random_device Raytracer::rd = std::random_device();
thread_local std::mt19937 Raytracer::rng = std::mt19937(Raytracer::rd());

Raytracer::Raytracer(){}

ImageWrapper<double> Raytracer::render(const Camera& camera, Model** Model_array, int num_Models, int resolution_x, int resolution_y, int num_samples, int max_reflections) const{
    ImageWrapper<double> arr(resolution_x, resolution_y, 3);

    BVHNode* scene_bvh = new BVHNode(Model_array, num_Models, camera.time_start, camera.time_end);

    std::uniform_real_distribution<double> dist;

    for(int j = arr.y() - 1; j >= 0; j--){
        for(int i = 0; i < arr.x(); i++){
            vec3 this_color(0, 0, 0);
            for(int s = 0; s < num_samples; s++){
                double u = double(i + dist(Raytracer::rng)) / double(arr.x());
                double v = double(j + dist(Raytracer::rng)) / double(arr.y());

                Ray ray = camera.cast_ray(u, v);

                this_color += color(ray, scene_bvh, 0, max_reflections);
            }

            this_color /= num_samples;
            
            arr.set(this_color.r(), i, j, 0);
            arr.set(this_color.g(), i, j, 1);
            arr.set(this_color.b(), i, j, 2);
        }
    }
    
    delete scene_bvh;

    return arr;
}

vec3 Raytracer::color(const Ray& ray, BVHNode* bvh, int ray_depth, int max_ray_depth) const{
    // test for a hit
    hit_record rec;
    if(bvh->hit(ray, 0.001, std::numeric_limits<double>::max(), rec)){
        // if there's a hit, color according to the hit
        Ray scattered;
        vec3 attenuation;

        // check if the material will scatter the ray
        if(ray_depth < max_ray_depth && rec.material->scatter(ray, rec, attenuation, scattered)){
            // if it does, then apply the color change from that reflection and continue on
            return attenuation * color(scattered, bvh, ray_depth + 1, max_ray_depth);
        } else {
            // otherwise we can assume the ray was "absorbed", just return black.
            return vec3(0);
        }
    } else {
        // otherwise, color according to the background color
        vec3 ray_hat = ray.direction().normalized();
        double t = .5 * (ray_hat.y() + 1);

        return (1.0 - t) * vec3(1,1,1) + t * vec3(.5,.7,1);
    }
}

bool Raytracer::hit_list(const Ray& ray, double t_min, double t_max, Model** Model_array, int num_Models, hit_record& rec) const{
    hit_record hit;

    bool hit_recorded = false;

    double closest_hit = t_max;
    for(int i = 0; i < num_Models; i++){
        if(Model_array[i]->hit(ray, t_min, closest_hit, hit)){
            hit_recorded = true;
            closest_hit = hit.t;
            rec = hit;
        }
    }

    return hit_recorded;
}