#include "AxisAlignedBoundingBox.h"

#include <utility>
#include <cmath>

AxisAlignedBoundingBox::AxisAlignedBoundingBox(){
    
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const vec3& min, const vec3& max){
    this->m_min = min;
    this->m_max = max;
}

AxisAlignedBoundingBox AxisAlignedBoundingBox::operator+(const AxisAlignedBoundingBox& rhs) const{
    vec3 min(
        std::fmin(this->m_min.x(), rhs.m_min.x()),
        std::fmin(this->m_min.y(), rhs.m_min.y()),
        std::fmin(this->m_min.z(), rhs.m_min.z())
    );

    vec3 max(
        std::fmax(this->m_max.x(), rhs.m_max.x()),
        std::fmax(this->m_max.y(), rhs.m_max.y()),
        std::fmax(this->m_max.z(), rhs.m_max.z())
    );

    return AxisAlignedBoundingBox(min, max);
}

vec3 AxisAlignedBoundingBox::min() const{
    return this->m_min;
}

vec3 AxisAlignedBoundingBox::max() const{
    return this->m_max;
}

bool AxisAlignedBoundingBox::hit(const Ray& ray_in, double t_min, double t_max) const{
    for(int axis = 0; axis < 3; axis++){
        double inverse_direction = 1.0 / ray_in.direction()[axis];

        double t_0 = (m_min[axis] - ray_in.origin()[axis]) * inverse_direction;
        double t_1 = (m_max[axis] - ray_in.origin()[axis]) * inverse_direction;

        if(inverse_direction < 0.0){
            std::swap(t_0, t_1);
        }

        t_min = t_0 > t_min ? t_0 : t_min;
        t_max = t_1 < t_max ? t_1 : t_max;

        if(t_max <= t_min){
            return false;
        }
    }

    return true;
}
