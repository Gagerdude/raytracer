#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "Model.h"
#include "AxisAlignedBoundingBox.h"

class BVHNode: public Model{
    public:
        BVHNode();
        ~BVHNode();
        BVHNode(Model** models, int num_models, double time_start, double time_end);

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

        Model* m_left;
        Model* m_right;

        AxisAlignedBoundingBox m_box;
};

#endif