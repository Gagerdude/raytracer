#include "Ray.h"

Ray::Ray(){

}

Ray::Ray(const vec3& origin, const vec3& direction){
    this->m_origin = origin;
    this->m_direction = direction;
}

vec3 Ray::origin() const{
    return this->m_origin;
}

vec3 Ray::direction() const{
    return this->m_origin;
}

vec3 Ray::point_on_ray(float t){
    return this->m_origin + t * this->m_direction;
}