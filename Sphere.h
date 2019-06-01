#ifndef SPHERE_H
#define SPHERE_H

#include "model.h"
#include "vec3.h"
#include "Ray.h"

class Sphere: public model {
    public:
        Sphere();
        Sphere(vec3 c, float r);
        virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const;
        
        vec3 center;
        float radius;
};

#endif