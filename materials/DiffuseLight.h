#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H

#include "Material.h"
#include "Texture.h"

class DiffuseLight: public Material{
    public:
        DiffuseLight(Texture* a);
        virtual ~DiffuseLight();
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const;
        virtual vec3 emitted(float u, float v, const vec3& p) const;

    private:
        Texture* emit;
};

#endif