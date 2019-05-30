#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray{
    public:
        Ray();
        Ray(const vec3& origin, const vec3& direction);

        vec3 origin() const;
        vec3 direction() const;

        vec3 point_on_ray(float t);

    private:
        vec3 m_origin, m_direction;
};

#endif