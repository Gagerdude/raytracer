#include "BVHNode.h"

#include "Raytracer.h"

#include <algorithm>

BVHNode::BVHNode(){

}

BVHNode::BVHNode(Model** models, int num_models, double time_start, double time_end){
    std::uniform_int_distribution<int> rand_axis(0, 2);
    int axis = rand_axis(Raytracer::rng);

    if(axis == 0){
        std::sort(models, models + num_models, [](const Model* lhs, const Model* rhs){
            AxisAlignedBoundingBox box_left, box_right;
            
            lhs->bounding_box(0, 0, box_left);
            rhs->bounding_box(0, 0, box_right);
                
            return box_left.min().x() > box_right.min().x();
        });
    } else if(axis == 1){
        std::sort(models, models + num_models, [](const Model* lhs, const Model* rhs){
            AxisAlignedBoundingBox box_left, box_right;
            
            lhs->bounding_box(0, 0, box_left);
            rhs->bounding_box(0, 0, box_right);
                
            return box_left.min().y() > box_right.min().y();
        });
    } else {
        std::sort(models, models + num_models, [](const Model* lhs, const Model* rhs){
            AxisAlignedBoundingBox box_left, box_right;
            
            lhs->bounding_box(0, 0, box_left);
            rhs->bounding_box(0, 0, box_right);
                
            return box_left.min().z() > box_right.min().z();
        });
    }

    if(num_models == 1){
        m_left = models[0];
        m_right = models[0];
    } else if(num_models == 2){
        m_left = models[0];
        m_right = models[1];
    } else {
        m_left = new BVHNode(models, num_models / 2, time_start, time_end);
        m_right = new BVHNode(models + num_models / 2, num_models - (num_models / 2), time_start, time_end);
    }

    AxisAlignedBoundingBox box_left, box_right;
    m_left->bounding_box(time_start, time_end, box_left);
    m_right->bounding_box(time_start, time_end, box_right);

    m_box = box_left + box_right;
}

bool BVHNode::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    if(m_box.hit(r, t_min, t_max)){
        hit_record rec_left, rec_right;

        bool hit_left = m_left->hit(r, t_min, t_max, rec_left);
        bool hit_right = m_right->hit(r, t_min, t_max, rec_right);

        if(hit_left && hit_right){
            rec = rec_left.t < rec_right.t ? rec_left : rec_right;
            return true;
        } else if(hit_left){
            rec = rec_left;
            return true;
        } else if(hit_right){
            rec = rec_right;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool BVHNode::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    box = this->m_box;
    return true;
}
