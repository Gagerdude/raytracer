#include "Raytracer.h"
#include "ImageWrapper.h"
#include "Camera.h"
#include "PNGWriter.h"

#include <limits>
#include <random>

Raytracer::Raytracer(){
    num_models = 0;
    models = nullptr;
}

void Raytracer::setResolution(int w, int h){
    width = w;
    height = h;
}

void Raytracer::setNumSamplesPerPixel(int samples){
    num_samples = samples;
}

void Raytracer::setModels(model** model_array, int array_size){
    models = model_array;
    num_models = array_size;
}

void Raytracer::render(std::string filename) const{
    float aspect_ratio = float(width) / float(height); 
    
    ImageWrapper<float> arr(width,height,3);
    
    Camera cam(aspect_ratio);

    std::default_random_engine generator;
    std::uniform_real_distribution rand_dist;

    for(int j = arr.y() - 1; j >= 0; j--){
        for(int i = 0; i < arr.x(); i++){
            vec3 this_color(0, 0, 0);
            for(int s = 0; s < num_samples; s++){
                float u = float(i + rand_dist(generator)) / float(arr.x());
                float v = float(j + rand_dist(generator)) / float(arr.y());

                Ray ray = cam.cast_ray(u, v);

                this_color += color(ray);
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

vec3 Raytracer::color(const Ray& ray) const{
    // test for a hit
    hit_record rec;
    if(hit_list(ray, 0, std::numeric_limits<float>::max(), rec)){
        // if there's a hit, color according to the hit
        return .5 * (rec.normal + vec3(1,1,1));
    } else {
        // otherwise, color according to the background color
        vec3 ray_hat = ray.direction().normalized();
        float u = .5 * (ray_hat.x() + 1.0);
        float v = .5 * (ray_hat.y() + 1.0);

        return vec3(u * 1.0, v * 1.0, .2);
    }
}

bool Raytracer::hit_list(const Ray& ray, float t_min, float t_max, hit_record& rec) const{
    hit_record hit;

    bool hit_recorded = false;

    float closest_hit = t_max;
    for(int i = 0; i < num_models; i++){
        if(models[i]->hit(ray, t_min, closest_hit, hit)){
            hit_recorded = true;
            closest_hit = hit.t;
            rec = hit;
        }
    }

    return hit_recorded;
}