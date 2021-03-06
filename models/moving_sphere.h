#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "Model.h"
#include "Material.h"
#include "vec3.h"
#include "Ray.h"

class moving_sphere: public Model {
    public:
        moving_sphere();
        ~moving_sphere();
        moving_sphere(vec3 c_start, vec3 c_end, double t_start, double t_end, double r, Material* mat);
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        vec3 center(double time) const;
        vec3 center_start, center_end;
        double time_start, time_end;
        double radius;

        Material* material;

        void get_uv(const vec3& p, double& u, double& v) const;
};

#endif
