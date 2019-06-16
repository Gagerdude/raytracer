#ifndef AXIS_ALIGNED_BOUNDING_BOX_H
#define AXIS_ALIGNED_BOUNDING_BOX_H

#include "vec3.h"
#include "Ray.h"

class AxisAlignedBoundingBox{
    public:
        AxisAlignedBoundingBox();
        AxisAlignedBoundingBox(const vec3& min, const vec3& max);

        vec3 min() const;
        vec3 max() const;

        bool hit(const Ray& ray_in, double t_min, double t_max) const;

    private:
        vec3 m_min, m_max;
};

#endif