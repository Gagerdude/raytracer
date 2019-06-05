#include "Camera.h"

Camera::Camera(double aspect_ratio){
    lower_left_corner = vec3(-aspect_ratio, -1.0, -1.0);
    horizontal = vec3(2 * aspect_ratio, 0.0, 0.0);
    vertical = vec3(0.0, 2.0, 0.0);
    origin = vec3(0.0, 0.0, 0.0);
}

Ray Camera::cast_ray(double u, double v) const{
    return Ray(origin, lower_left_corner + (u * horizontal) + (v * vertical));
}