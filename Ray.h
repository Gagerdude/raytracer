#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray{
    public:
        Ray();
        Ray(const vec3& origin, const vec3& direction, double time = 0);

        vec3 origin() const;
        vec3 direction() const;
        double time() const;

        vec3 point_on_ray(double t) const;

    private:
        vec3 m_origin, m_direction;
        double m_time;
};

#endif