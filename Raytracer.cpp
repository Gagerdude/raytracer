#include "Raytracer.h"
#include "ImageWrapper.h"
#include "Camera.h"
#include "PNGWriter.h"

#include <limits>
#include <random>

Raytracer::Raytracer(){}

void Raytracer::render(std::string filename, model** model_array, int num_models, int resolution_x, int resolution_y, int num_samples, int max_reflections) const{
    float aspect_ratio = float(resolution_x) / float(resolution_y); 
    
    ImageWrapper<float> arr(resolution_x, resolution_y, 3);
    
    Camera cam(aspect_ratio);

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution rand_dist;

    for(int j = arr.y() - 1; j >= 0; j--){
        for(int i = 0; i < arr.x(); i++){
            vec3 this_color(0, 0, 0);
            for(int s = 0; s < num_samples; s++){
                float u = float(i + rand_dist(generator)) / float(arr.x());
                float v = float(j + rand_dist(generator)) / float(arr.y());

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
    if(hit_list(ray, 0, std::numeric_limits<float>::max(), model_array, num_models, rec) && ray_depth < 10){
        // if there's a hit, color according to the hit
        std::random_device rand_dev;
        std::mt19937 gen(rand_dev());
        std::uniform_real_distribution rand_dist;

        vec3 rand_vec(rand_dist(gen), rand_dist(gen), rand_dist(gen));
        rand_vec.normalize();

        vec3 refl_vec = rec.p + rec.normal + rand_vec;

        return .5 * color(Ray(rec.p, refl_vec - rec.p), model_array, num_models, ray_depth + 1, max_ray_depth);
    } else {
        // otherwise, color according to the background color
        vec3 ray_hat = ray.direction().normalized();
        float t = .5 * (ray_hat.y() + 1);

        return (1.0 - t) * vec3(1,1,1) + t * vec3(.5,.7,1);
    }
}

bool Raytracer::hit_list(const Ray& ray, float t_min, float t_max, model** model_array, int num_models, hit_record& rec) const{
    hit_record hit;

    bool hit_recorded = false;

    float closest_hit = t_max;
    for(int i = 0; i < num_models; i++){
        if(model_array[i]->hit(ray, t_min, closest_hit, hit)){
            hit_recorded = true;
            closest_hit = hit.t;
            rec = hit;
        }
    }

    return hit_recorded;
}