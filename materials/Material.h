#ifndef MATERIAL_H
#define MATERIAL_H

#include "../engine/Ray.h"
#include "../models/Model.h"

class Material {
    public:
        virtual ~Material(){}
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const = 0;
};

#endif