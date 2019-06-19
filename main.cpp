#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include <future>

#include "Raytracer.h"
#include "PNGWriter.h"

#include "vec3.h"
#include "Camera.h"

#include "Model.h"
#include "Sphere.h"
#include "moving_sphere.h"

#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

#include "ConstantTexture.h"
#include "CheckeredTexture.h"

void get_params(int argc, char** argv, int& res_x, int& res_y, int& num_samples, int& num_threads, int& max_refl){
    while(argc > 2){
        argv++;
        if(std::strcmp(*argv, "-xres") == 0){
            res_x = std::stoi(*++argv);
            argc--;
        } else if(std::strcmp(*argv, "-yres") == 0){
            res_y = std::stoi(*++argv);
            argc--;
        } else if(std::strcmp(*argv, "-nsamples") == 0){
            num_samples = std::stoi(*++argv);
            argc--;
        } else if(std::strcmp(*argv, "-nthreads") == 0) {
            num_threads = std::stoi(*++argv);
            argc--;
        } else if(std::strcmp(*argv, "-nrefl") == 0){
            max_refl = std::stoi(*++argv);
            argc--;
        }
        argc--;
    }
}

std::string make_filename(int xres, int yres, int samples, int refl_depth){
    std::string filename;

    filename += "images/test";
    filename += '_';
    filename += std::to_string(xres);
    filename += 'x';
    filename += std::to_string(yres);
    filename += '_';
    filename += std::to_string(samples);
    filename += '_';
    filename += std::to_string(refl_depth);
    filename += ".png";

    return filename;
}

Camera make_camera(double aspect_ratio){
    vec3 camera_origin(13, 2, 3);
    vec3 camera_target(0, 0, 0);
    vec3 camera_up(0, 1, 0);

    double camera_fov = 40;

    double apeture_size = 0;
    double focal_length = (camera_origin - camera_target).length();

    return Camera(camera_origin, camera_target, camera_up, camera_fov, aspect_ratio, apeture_size, focal_length, 0, 1);
}

std::vector<Model*> random_scene(){
    std::vector<Model*> list;

    list.push_back(new Sphere(vec3(0,-1000, 0), 1000, new Lambertian(new CheckeredTexture(new ConstantTexture(vec3(.2, .3, .1)), new ConstantTexture(vec3(.9, .9, .9))))));

    std::uniform_real_distribution<double> dist;

    Raytracer::rng.seed(Raytracer::rng.default_seed);

    for(int a = -11; a < 11; a++){
        for(int b = -11; b < 11; b++){
            double choose_mat = dist(Raytracer::rng);
            vec3 center(a + .9 * dist(Raytracer::rng), .2, b + .9 * dist(Raytracer::rng));
            if((center-vec3(4,.2,0)).length() > .9){
                if(choose_mat < .8){    // diffuse
                    vec3 color(dist(Raytracer::rng)*dist(Raytracer::rng), dist(Raytracer::rng)*dist(Raytracer::rng), dist(Raytracer::rng)*dist(Raytracer::rng));
                    list.push_back(new moving_sphere(center, center + vec3(0, .5*dist(Raytracer::rng), 0), 0, 1, .2, new Lambertian(new ConstantTexture(color))));
                } else if(choose_mat < .95){    // metal
                    vec3 color(.5 * (1 + dist(Raytracer::rng)), .5 * (1 + dist(Raytracer::rng)), .5 * (1 + dist(Raytracer::rng)));
                    list.push_back(new Sphere(center, .2, new Metal(new ConstantTexture(color), dist(Raytracer::rng))));
                } else {    // glass
                    list.push_back(new Sphere(center, .2, new Dielectric(1.5)));
                }
            }
        }
    }

    list.push_back(new Sphere(vec3(0,1,0), 1, new Dielectric(1.5)));
    list.push_back(new Sphere(vec3(-4,1,0), 1, new Lambertian(new ConstantTexture(vec3(.4,.2,.1)))));
    list.push_back(new Sphere(vec3(4,1,0), 1, new Metal(new ConstantTexture(vec3(.7,.6,.5)), 0)));

    std::random_device rd;
    Raytracer::rng.seed(rd());

    return list;
}

std::vector<Model*> two_spheres_scene(){
    std::vector<Model*> list;

    list.push_back(new Sphere(vec3(0,-10,0), 10, new Lambertian(new CheckeredTexture(new ConstantTexture(vec3(.2,.3,.1)), new ConstantTexture(vec3(.9,.9,.9))))));
    list.push_back(new Sphere(vec3(0,10,0), 10, new Lambertian(new CheckeredTexture(new ConstantTexture(vec3(.2,.3,.1)), new ConstantTexture(vec3(.9,.9,.9))))));

    return list;
}

int main(int argc, char** argv){
    Raytracer raytracer;

    int res_x = 1600;
    int res_y = 900;
    int num_samples = 100;
    int num_threads = std::thread::hardware_concurrency();
    if(num_threads == 0){
        num_threads = 1;
    }
    int max_reflections = 50;

    // see if anything was passed in as a command line parameter
    get_params(argc, argv, res_x, res_y, num_samples, num_threads, max_reflections);

    Camera cam = make_camera(double(res_x) / double(res_y));
    
    std::vector<Model*> list = random_scene();
    // std::vector<Model*> list = two_spheres_scene();
    
    std::string filename = make_filename(res_x, res_y, num_samples, max_reflections);

    ImageWrapper<double> image = raytracer.render(cam, list.data(), list.size(), res_x, res_y, num_samples, max_reflections, num_threads);

    PNGWriter png(filename);
    png.write(image);
}