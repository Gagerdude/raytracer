#include "Ray.h"

Ray::Ray(){

}

Ray::Ray(const vec3& origin, const vec3& direction, double time){
    this->m_origin = origin;
    this->m_direction = direction;
    this->m_time = time;
}

vec3 Ray::origin() const{
    return this->m_origin;
}

vec3 Ray::direction() const{
    return this->m_direction;
}

double Ray::time() const{
    return this->m_time;
}

vec3 Ray::point_on_ray(double t) const{
    return this->m_origin + t * this->m_direction;
}