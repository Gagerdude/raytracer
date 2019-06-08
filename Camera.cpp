#include "Camera.h"

#include <cmath>

Camera::Camera(vec3 origin_in, vec3 target, vec3 up, double horizontal_fov, double aspect_ratio){
    double theta = horizontal_fov * M_PI / 180;
    double half_width = std::tan(theta / 2);
    double half_height = half_width / aspect_ratio;

    vec3 w = (origin_in - target).normalized();
    vec3 u = cross(up, w).normalized();
    vec3 v = cross(w, u);

    lower_left_corner = vec3(-half_width, -half_height, -1.0);
    lower_left_corner = origin - half_width*u -half_height*v - w;
    horizontal = 2 * half_width * u;
    vertical = 2 * half_height * v;
    origin = origin_in;
}

Ray Camera::cast_ray(double u, double v) const{
    return Ray(origin, lower_left_corner + (u * horizontal) + (v * vertical));
}