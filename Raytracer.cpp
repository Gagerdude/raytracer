#include "Raytracer.h"
#include "ImageWrapper.h"
#include "Camera.h"
#include "PNGWriter.h"

#include <limits>
#include <random>

#include <iostream>

Raytracer::Raytracer(){
    std::random_device rand_dev;
    this->generator.seed(rand_dev());
    this->rng = std::bind(rand_dist, std::ref(generator));
}

void Raytracer::render(std::string filename, model** model_array, int num_models, int resolution_x, int resolution_y, int num_samples, int max_reflections) const{
    double aspect_ratio = double(resolution_x) / double(resolution_y); 
    
    ImageWrapper<double> arr(resolution_x, resolution_y, 3);
    
    Camera cam(aspect_ratio);

    for(int j = arr.y() - 1; j >= 0; j--){
        for(int i = 0; i < arr.x(); i++){
            vec3 this_color(0, 0, 0);
            for(int s = 0; s < num_samples; s++){
                double u = double(i + rng()) / double(arr.x());
                double v = double(j + rng()) / double(arr.y());

                Ray ray = cam.cast_ray(u, v);

                this_color += color(ray, model_array, num_models, 0, max_reflections);
            }

            this_color /= num_samples;
            
            arr.set(this_color.r(), i, j, 0);
            arr.set(this_color.g(), i, j, 1);
            arr.set(this_color.b(), i, j, 2);
        }
    }
    
    PNGWriter tst(filename);
    tst.write(arr);
}

vec3 Raytracer::color(const Ray& ray, model** model_array, int num_models, int ray_depth, int max_ray_depth) const{
    // test for a hit
    hit_record rec;
    if(hit_list(ray, 0.001, std::numeric_limits<double>::max(), model_array, num_models, rec) && ray_depth < 10){
        // if there's a hit, color according to the hit
        vec3 rand_vec(rng(), rng(), rng());
        rand_vec.normalize();

        vec3 refl_vec = rec.p + rec.normal + rand_vec;

        return .5 * color(Ray(rec.p, refl_vec - rec.p), model_array, num_models, ray_depth + 1, max_ray_depth);
    } else {
        // otherwise, color according to the background color
        vec3 ray_hat = ray.direction().normalized();
        double t = .5 * (ray_hat.y() + 1);

        return (1.0 - t) * vec3(1,1,1) + t * vec3(.5,.7,1);
    }
}

bool Raytracer::hit_list(const Ray& ray, double t_min, double t_max, model** model_array, int num_models, hit_record& rec) const{
    hit_record hit;

    bool hit_recorded = false;

    double closest_hit = t_max;
    for(int i = 0; i < num_models; i++){
        if(model_array[i]->hit(ray, t_min, closest_hit, hit)){
            hit_recorded = true;
            closest_hit = hit.t;
            rec = hit;
        }
    }

    return hit_recorded;
}