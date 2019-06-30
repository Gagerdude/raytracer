#include "Camera.h"

#include "Raytracer.h"

#include <cmath>
#include <random>

Camera::Camera(vec3 origin_in, vec3 target, vec3 up, double fov, double aspect_ratio, double aperture, double focus_dist, double _time_start, double _time_end){
    time_start = _time_start;
    time_end = _time_end;
    
    lens_radius = aperture / 2;
    
    double theta = fov * M_PI / 180;
    double half_height = std::tan(theta / 2);
    double half_width = half_height * aspect_ratio;

    w = (origin_in - target).normalized();
    u = cross(up, w).normalized();
    v = cross(w, u);

    lower_left_corner = origin_in - half_width*focus_dist*u -half_height*focus_dist*v - focus_dist*w;
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
    origin = origin_in;
}

Ray Camera::cast_ray(double s, double t) const{
    std::uniform_real_distribution<double> unit_rng(-1, 1);
    std::uniform_real_distribution<double> time_rng(time_start, time_end);

    vec3 random_disk = lens_radius * vec3(unit_rng(Raytracer::rng), unit_rng(Raytracer::rng), 0).normalized();
    vec3 offset = u * random_disk.x() + v * random_disk.y();
    return Ray(origin + offset, lower_left_corner + (s * horizontal) + (t * vertical) - origin - offset, time_rng(Raytracer::rng));
}
