#ifndef MODEL_H
#define MODEL_H

#include "Ray.h"

struct hit_record {
    double t;
    vec3 p;
    vec3 normal;
};

class model{
    public:
        virtual ~model(){};
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif