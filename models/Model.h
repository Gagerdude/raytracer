#ifndef MODEL_H
#define MODEL_H

#include "Ray.h"
#include "AxisAlignedBoundingBox.h"

class Material;

struct hit_record {
    double t;
    vec3 p;
    vec3 normal;
    Material* material;
};

class Model{
    public:
        virtual ~Model(){};
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const = 0;
};

#endif