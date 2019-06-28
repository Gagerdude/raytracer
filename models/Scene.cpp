#include "Scene.h"

Scene::Scene(Model** models, int num_models){
    scene = new Model*[num_models];
    scene_size = num_models;
    for(int i = 0; i < num_models; i++){
        scene[i] = models[i];
    }
}

Scene::~Scene(){
    for(int i = 0; i < scene_size; i++){
        delete scene[i];
    }
    delete[] scene;
}

bool Scene::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    hit_record hit;

    bool hit_recorded = false;

    double closest_hit = t_max;
    for(int i = 0; i < scene_size; i++){
        if(scene[i]->hit(r, t_min, closest_hit, hit)){
            hit_recorded = true;
            closest_hit = hit.t;
            rec = hit;
        }
    }

    return hit_recorded;
}

bool Scene::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    AxisAlignedBoundingBox temp;

    for(int i = 0; i < scene_size; i++){
        if(scene[i]->bounding_box(time_start, time_end, temp)){
            box = box + temp;
        }
    }

    return true;
}
