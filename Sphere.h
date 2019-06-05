#ifndef SPHERE_H
#define SPHERE_H

#include "model.h"
#include "vec3.h"
#include "Ray.h"

class Sphere: public model {
    public:
        Sphere();
        Sphere(vec3 c, double r);
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        
        vec3 center;
        double radius;
};

#endif