#ifndef WRAPPER_H
#define WRAPPER_H

#include "Material.h"

#include "Ray.h"
#include "Model.h"

class Wrapper: public Material {
    public:
        Wrapper(Material* material);
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const;
        virtual vec3 emitted(float u, float v, const vec3& p) const;

    private:
        Material* m_material;
};

#endif