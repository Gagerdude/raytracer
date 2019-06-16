#ifndef SPHERE_H
#define SPHERE_H

#include "Model.h"
#include "Material.h"
#include "vec3.h"
#include "Ray.h"

class Sphere: public Model {
    public:
        Sphere();
        ~Sphere();
        Sphere(vec3 c, double r, Material* mat);
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

        vec3 center;
        double radius;

        Material* material;
};

#endif