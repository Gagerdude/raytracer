#ifndef METAL_H
#define METAL_H

#include "Material.h"
#include "Texture.h"

class Metal: public Material {
    public:
        Metal(Texture* a, double f);
        ~Metal();
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const;
    
    private:
        Texture* albedo;
        double fuzz;
};

#endif