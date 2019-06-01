#include "Sphere.h"

#include <math.h>

Sphere::Sphere(){

}

Sphere::Sphere(vec3 c, float r){
    center = c;
    radius = r;
}

bool Sphere::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const{
    // get the ray to the center of the sphere
    vec3 origin_to_center = r.origin() - center;

    // get the numbers needed to solve for the ray intersection.
    // check for solutions using quadratic formula
    float a = dot(r.direction(), r.direction());
    float b = 2 * dot(origin_to_center, r.direction());
    float c = dot(origin_to_center, origin_to_center) - radius * radius;

    float discriminant = b*b - 4*a*c;

    // first, check if a solution exists
    if(discriminant > 0){
        float t = (-b - sqrt(discriminant)) / (2 * a);
        
        // check if the solution is within our bounds...
        if(t_min < t && t < t_max){
            // it is, so record the hit and return true
            rec.t = t;
            rec.p = r.point_on_ray(t);
            rec.normal = (rec.p - center) / radius;

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

            return true;
        }
    }

    return false;
}