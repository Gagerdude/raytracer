#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Model.h"

class Material {
    public:
        virtual ~Material(){}
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const = 0;
        virtual vec3 emitted(float u, float v, const vec3& p) const{
            return vec3(0);
        }
};

#endif