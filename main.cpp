#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include <future>

#include "Raytracer.h"
#include "PNGWriter.h"
#include "PNGReader.h"

#include "vec3.h"
#include "Camera.h"

#include "Model.h"
#include "Sphere.h"
#include "moving_sphere.h"
#include "RectangleXY.h"
#include "RectangleXZ.h"
#include "RectangleYZ.h"
#include "Box.h"
#include "ConstantMedium.h"

#include "Translate.h"
#include "RotateY.h"

#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "DiffuseLight.h"

#include "ConstantTexture.h"
#include "CheckeredTexture.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"

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

Camera make_cornell_camera(double aspect_ratio){
    vec3 camera_origin(278, 278, -800);
    vec3 camera_target(278, 278, 0);
    vec3 camera_up(0, 1, 0);

    double camera_fov = 64;

    double apeture_size = 0;
    double focal_length = 10;

    return Camera(camera_origin, camera_target, camera_up, camera_fov, aspect_ratio, apeture_size, focal_length, 0, 1);
}

Camera make_final_camera(double aspect_ratio){
    vec3 camera_origin(550, 300, -550);
    vec3 camera_target(0, 300, 800);
    vec3 camera_up(0, 1, 0);

    double camera_fov = 40;

    double apeture_size = 0;
    double focal_length = 10;

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

std::vector<Model*> two_perlin_spheres_scene(){
    std::vector<Model*> list;

    list.push_back(new Sphere(vec3(0,-1000,0), 1000, new Lambertian(new NoiseTexture(4))));
    list.push_back(new Sphere(vec3(0,2,0), 2, new Lambertian(new NoiseTexture(4))));

    return list;
}

std::vector<Model*> earth_scene(){
    std::vector<Model*> list;

    PNGReader img("Earth.png");

    list.push_back(new Sphere(vec3(0,0,0), 2, new Lambertian(new ImageTexture(img.image))));

    return list;
}

std::vector<Model*> light_scene(){
    std::vector<Model*> list;

    list.push_back(new Sphere(vec3(0,-1000,0), 1000, new Lambertian(new NoiseTexture(4))));
    list.push_back(new Sphere(vec3(0,2,0), 2, new Lambertian(new NoiseTexture(4))));
    list.push_back(new Sphere(vec3(0,7,0), 2, new DiffuseLight(new ConstantTexture(vec3(4,4,4)))));
    list.push_back(new RectangleXY(3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture(vec3(4,4,4)))));

    return list;
}

std::vector<Model*> cornell_box_scene(){
    std::vector<Model*> list;

    list.push_back(new RectangleYZ(0, 555, 0, 555, 555, new Lambertian(new ConstantTexture(vec3(.12,.45,.15)))));
    list.push_back(new RectangleYZ(0, 555, 0, 555, 0, new Lambertian(new ConstantTexture(vec3(.65,.05,.05)))));
    list.push_back(new RectangleXZ(213, 343, 227, 332, 554, new DiffuseLight(new ConstantTexture(vec3(15,15,15)))));
    list.push_back(new RectangleXZ(0, 555, 0, 555, 555, new Lambertian(new ConstantTexture(vec3(.73,.73,.73)))));
    list.push_back(new RectangleXZ(0, 555, 0, 555, 0, new Lambertian(new ConstantTexture(vec3(.73,.73,.73)))));
    list.push_back(new RectangleXY(0, 555, 0, 555, 555, new Lambertian(new ConstantTexture(vec3(.73,.73,.73)))));

    list.push_back(new Translate(new RotateY(new Box(vec3(0), vec3(165), new Lambertian(new ConstantTexture(.73))), -18), vec3(130, 0, 65)));
    list.push_back(new Translate(new RotateY(new Box(vec3(0), vec3(165, 330, 165), new Lambertian(new ConstantTexture(.73))), 15), vec3(265, 0, 295)));

    return list;
}

std::vector<Model*> cornell_box_smoke_scene(){
    std::vector<Model*> list;

    list.push_back(new RectangleYZ(0, 555, 0, 555, 555, new Lambertian(new ConstantTexture(vec3(.12,.45,.15)))));
    list.push_back(new RectangleYZ(0, 555, 0, 555, 0, new Lambertian(new ConstantTexture(vec3(.65,.05,.05)))));
    list.push_back(new RectangleXZ(113, 443, 127, 432, 554, new DiffuseLight(new ConstantTexture(vec3(7,7,7)))));
    list.push_back(new RectangleXZ(0, 555, 0, 555, 555, new Lambertian(new ConstantTexture(vec3(.73,.73,.73)))));
    list.push_back(new RectangleXZ(0, 555, 0, 555, 0, new Lambertian(new ConstantTexture(vec3(.73,.73,.73)))));
    list.push_back(new RectangleXY(0, 555, 0, 555, 555, new Lambertian(new ConstantTexture(vec3(.73,.73,.73)))));

    list.push_back(new ConstantMedium(new Translate(new RotateY(new Box(vec3(0), vec3(165), new Lambertian(new ConstantTexture(.73))), -18), vec3(130, 0, 65)), .01, new ConstantTexture(vec3(1))));
    list.push_back(new ConstantMedium(new Translate(new RotateY(new Box(vec3(0), vec3(165, 330, 165), new Lambertian(new ConstantTexture(.73))), 15), vec3(265, 0, 295)), .01, new ConstantTexture(vec3(0))));

    return list;
}

std::vector<Model*> final_scene(){
    std::vector<Model*> list;

    std::uniform_real_distribution<double> dist;

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 20; j++){
            double w = 100;
            double x = -1000 + i * w;
            double z = -1000 + j * w;
            double y = 0;
            double x_1 = x + w;
            double y_1 = 100 * (dist(Raytracer::rng) + .01);
            double z_1 = z + w;

            list.push_back(new Box(vec3(x,y,z), vec3(x_1, y_1, z_1), new Lambertian(new ConstantTexture(vec3(.48, .83, .53)))));
        }
    }

    list.push_back(new RectangleXZ(123, 423, 147, 412, 554, new DiffuseLight(new ConstantTexture(vec3(7)))));
    
    vec3 center(400, 400, 200);
    list.push_back(new moving_sphere(center, center + vec3(30,0,0), 0, 1, 50, new Lambertian(new ConstantTexture(vec3(.7, .3, .1)))));

    list.push_back(new Sphere(vec3(260, 150, 45), 50, new Dielectric(1.5)));
    
    list.push_back(new Sphere(vec3(0, 150, 145), 50, new Metal(new ConstantTexture(vec3(.8, .8, .9)), 10)));
    
    list.push_back(new Sphere(vec3(360, 150, 147), 70, new Dielectric(1.5)));

    list.push_back(new ConstantMedium(new Sphere(vec3(360, 150, 147), 70, new Dielectric(1.5)), .2, new ConstantTexture(vec3(.2, .4, .9))));

    list.push_back(new ConstantMedium(new Sphere(vec3(0), 5000, new Dielectric(1.5)), .0001, new ConstantTexture(vec3(1))));

    PNGReader img("Earth.png");
    list.push_back(new Sphere(vec3(400, 200, 400), 100, new Lambertian(new ImageTexture(img.image))));

    list.push_back(new Sphere(vec3(220, 280, 300), 80, new Lambertian(new NoiseTexture(.1))));

    for(int i = 0; i < 1000; i++){
        list.push_back(new Translate(new RotateY(new Sphere(vec3(165 * dist(Raytracer::rng), 165 * dist(Raytracer::rng), 165 * dist(Raytracer::rng)), 10, new Lambertian(new ConstantTexture(vec3(.48, .83, .53)))), 15), vec3(-100, 270, 395)));
    }

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

    // Camera cam = make_camera(double(res_x) / double(res_y));
    // Camera cam = make_cornell_camera(double(res_x) / double(res_y));
    Camera cam = make_final_camera(double(res_x) / double(res_y));


    std::vector<Model*> list;
    // list = random_scene();
    // list = two_spheres_scene();
    // list = two_perlin_spheres_scene();
    // list = earth_scene();
    // list = light_scene();
    // list = cornell_box_scene();
    // list = cornell_box_smoke_scene();
    list = final_scene();
    
    std::string filename = make_filename(res_x, res_y, num_samples, max_reflections);

    ImageWrapper<double> image = raytracer.render(cam, list.data(), list.size(), res_x, res_y, num_samples, max_reflections, num_threads);

    PNGWriter png(filename);
    png.write(image);
}