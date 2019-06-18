#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"
#include "../textures/Texture.h"

class Lambertian: public Material {
    public:
        Lambertian(Texture* a);
        ~Lambertian();
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const;
    
    private:
        Texture* albedo;
};

#endif