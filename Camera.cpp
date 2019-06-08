#include "Camera.h"

#include <cmath>

Camera::Camera(double horizontal_fov, double aspect_ratio){
    double theta = horizontal_fov * M_PI / 180;
    double half_width = std::tan(theta / 2);
    double half_height = half_width / aspect_ratio;

    lower_left_corner = vec3(-half_width, -half_height, -1.0);
    horizontal = vec3(2 * half_width, 0.0, 0.0);
    vertical = vec3(0.0, 2 * half_height, 0.0);
    origin = vec3(0.0, 0.0, 0.0);
}

Ray Camera::cast_ray(double u, double v) const{
    return Ray(origin, lower_left_corner + (u * horizontal) + (v * vertical));
}