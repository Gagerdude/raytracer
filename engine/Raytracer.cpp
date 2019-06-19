#include "Raytracer.h"

#include <limits>
#include <random>
#include <functional>
#include <thread>

#include <iostream>


thread_local std::random_device Raytracer::rd = std::random_device();
thread_local std::mt19937 Raytracer::rng = std::mt19937(Raytracer::rd());

Raytracer::Raytracer(){}

ImageWrapper<double> Raytracer::render(const Camera& camera, Model** Model_array, int num_Models, int resolution_x, int resolution_y, int num_samples, int max_reflections, int num_threads) const{
    ImageWrapper<double> arr(resolution_x, resolution_y, 3);

    BVHNode* scene_bvh = new BVHNode(Model_array, num_Models, camera.time_start, camera.time_end);

    std::cout << "Working with " << num_threads << " threads" << std::endl;

    std::queue<std::function<void()>> work_queue;
    std::mutex work_queue_mutex;

    int target_block_size = 32;

    int block_count_x = (resolution_x < target_block_size) ? 1 : resolution_x / target_block_size;
    int block_count_y = (resolution_y < target_block_size) ? 1 : resolution_y / target_block_size;


    int x_left = resolution_x;
    for(int x = block_count_x; x > 0; x--){
        int block_res_x = x_left / x;

        int y_left = resolution_y;
        for(int y = block_count_y; y > 0; y--){
            int block_res_y = y_left / y;

            int start_x = resolution_x - x_left;
            int start_y = resolution_y - y_left;
            int end_x = start_x + block_res_x;
            int end_y = start_y + block_res_y;

            std::cout << start_x << ' ' << end_x << ' ' << start_y << ' ' << end_y << std::endl;

            work_queue.push(std::bind(&Raytracer::render_block, this, std::ref(arr), std::ref(camera), scene_bvh, start_x, end_x, start_y, end_y, num_samples, max_reflections));

            y_left -= block_res_y;
        }

        x_left -= block_res_x;
    }

    if(block_count_x * block_count_y < num_threads){
        num_threads = block_count_x * block_count_y;
    }

    std::vector<std::thread> threads;
    for(int i = 0; i < num_threads; i++){
        threads.push_back(std::thread(&Raytracer::render_async, this, std::ref(work_queue), std::ref(work_queue_mutex)));
    }
    for(int i = 0; i < num_threads; i++){
        threads[i].join();
        std::cout << "Joined " << i << " Threads" << std::endl;
    }
    
    delete scene_bvh;

    return arr;
}

void Raytracer::render_block(ImageWrapper<double>& img, const Camera& camera, BVHNode* scene, int x_start, int x_end, int y_start, int y_end, int num_samples, int max_reflections) const{
    std::uniform_real_distribution<double> dist;

    for(int j = y_start; j < y_end; j++){
        for(int i = x_start; i < x_end; i++){
            vec3 this_color(0, 0, 0);
            for(int s = 0; s < num_samples; s++){
                double u = double(i + dist(Raytracer::rng)) / double(img.x());
                double v = double(j + dist(Raytracer::rng)) / double(img.y());

                Ray ray = camera.cast_ray(u, v);

                this_color += color(ray, scene, 0, max_reflections);
            }

            this_color /= num_samples;
            
            img.set(this_color.r(), i, j, 0);
            img.set(this_color.g(), i, j, 1);
            img.set(this_color.b(), i, j, 2);
        }
    }
}

void Raytracer::render_async(std::queue<std::function<void()>>& work_queue, std::mutex& work_queue_mutex) const{
    work_queue_mutex.lock();
    
    while(!work_queue.empty()){
        std::function<void()> fnc = work_queue.front();
        work_queue.pop();
        std::cout << "Running again" << std::endl;
        work_queue_mutex.unlock();
        
        fnc();

        work_queue_mutex.lock();
    }

    work_queue_mutex.unlock();
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