#include "moving_sphere.h"

#include "Raytracer.h"

#include <math.h>
#include <random>

moving_sphere::moving_sphere(){
    center_start = vec3();
    center_end = vec3();
    time_start = 0;
    time_end = 0;
    radius = 0;
    material = nullptr;
}

moving_sphere::moving_sphere(vec3 c_start, vec3 c_end, double t_start, double t_end, double r, Material* mat){
    center_start = c_start;
    center_end = c_end;
    time_start = t_start;
    time_end = t_end;
    radius = r;
    material = mat;
}

moving_sphere::~moving_sphere(){
    delete material;
}

bool moving_sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    // get the ray to the center of the sphere
    vec3 origin_to_center = r.origin() - center(r.time());

    // get the numbers needed to solve for the ray intersection.
    // check for solutions using quadratic formula
    double a = dot(r.direction(), r.direction());
    double b = 2 * dot(origin_to_center, r.direction());
    double c = dot(origin_to_center, origin_to_center) - radius * radius;

    double discriminant = b*b - 4*a*c;

    // first, check if a solution exists
    if(discriminant > 0){
        double t = (-b - sqrt(discriminant)) / (2 * a);
        
        // check if the solution is within our bounds...
        if(t_min < t && t < t_max){
            // it is, so record the hit and return true
            rec.t = t;
            rec.p = r.point_on_ray(t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.material = material;

            get_uv(rec.normal, rec.u, rec.v);

            return true;
        }

        // quadratic equation is +-, so check the other half
        t = (-b + sqrt(discriminant)) / (2 * a);

        // check if the second solution lies within the bounds
        if(t_min < t && t < t_max){
            // it is, so record the hit and return true
            rec.t = t;
            rec.p = r.point_on_ray(t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.material = material;

            get_uv(rec.normal, rec.u, rec.v);

            return true;
        }
    }

    return false;
}

bool moving_sphere::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    AxisAlignedBoundingBox box_start(center_start - vec3(radius), center_start + vec3(radius));
    AxisAlignedBoundingBox box_end(center_end - vec3(radius), center_end + vec3(radius));

    box = box_start + box_end;
    return true;
}

vec3 moving_sphere::center(double time) const{
    return center_start + ((time - time_start) / (time_end - time_start)) * (center_end - center_start);
}

void moving_sphere::get_uv(const vec3& p, double& u, double& v) const{
    double phi = std::atan2(p.z(), p.x());
    double theta = std::asin(p.y());

    u = (1 - (phi + M_PI)) / (2 * M_PI);
    v = (theta + M_PI_2) / M_PI;
}
