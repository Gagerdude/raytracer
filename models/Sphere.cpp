#include "Sphere.h"

#include <math.h>

Sphere::Sphere(){
    center = vec3();
    radius = 0;
    material = nullptr;
}

Sphere::Sphere(vec3 c, double r, Material* mat){
    center = c;
    radius = r;
    material = mat;
}

Sphere::~Sphere(){
    delete material;
}

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    // get the ray to the center of the sphere
    vec3 origin_to_center = r.origin() - center;

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
            rec.normal = (rec.p - center) / radius;
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
            rec.normal = (rec.p - center) / radius;
            rec.material = material;

            get_uv(rec.normal, rec.u, rec.v);

            return true;
        }
    }

    return false;
}

bool Sphere::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    box = AxisAlignedBoundingBox(center - vec3(radius), center + vec3(radius));
    return true;
}

void Sphere::get_uv(const vec3& p, double& u, double& v) const{
    double phi = std::atan2(p.z(), p.x());
    double theta = std::asin(p.y());

    u = (1 - (phi + M_PI)) / (2 * M_PI);
    v = (theta + M_PI_2) / M_PI;
}
