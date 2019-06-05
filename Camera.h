#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "Ray.h"

class Camera{
    public:
        Camera(double aspect_ratio);

        Ray cast_ray(double u, double v) const;

        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 origin;
};

#endif