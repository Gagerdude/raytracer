#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "Material.h"

#include "Texture.h"

class Isotropic: public Material {
    public:
        Isotropic(Texture* albedo);
        ~Isotropic();
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const;

    private:
        Texture* m_albedo;
};

#endif