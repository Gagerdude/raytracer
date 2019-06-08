#include "Camera.h"

#include "Raytracer.h"

#include <cmath>
#include <random>

Camera::Camera(vec3 origin_in, vec3 target, vec3 up, double horizontal_fov, double aspect_ratio, double aperture, double focus_dist){
    lens_radius = aperture / 2;
    
    double theta = horizontal_fov * M_PI / 180;
    double half_width = std::tan(theta / 2);
    double half_height = half_width / aspect_ratio;

    w = (origin_in - target).normalized();
    u = cross(up, w).normalized();
    v = cross(w, u);

    lower_left_corner = origin_in - half_width*focus_dist*u -half_height*focus_dist*v - focus_dist*w;
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
    origin = origin_in;
}

Ray Camera::cast_ray(double s, double t) const{
    std::uniform_real_distribution<double> dist(-1, 1);
    vec3 random_disk = lens_radius * vec3(dist(Raytracer::rng), dist(Raytracer::rng), 0).normalized();
    vec3 offset = u * random_disk.x() + v * random_disk.y();
    return Ray(origin + offset, lower_left_corner + (s * horizontal) + (t * vertical) - origin - offset);
}