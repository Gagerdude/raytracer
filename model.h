#ifndef MODEL_H
#define MODEL_H

#include "Ray.h"

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
};

class model{
    public:
        virtual bool hit(const Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif