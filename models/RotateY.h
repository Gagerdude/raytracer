#ifndef ROTATEY_H
#define ROTATEY_H

#include "Model.h"

class RotateY: public Model{
    public:
        RotateY(Model* model, double theta);
        ~RotateY();
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        Model* m_model;
        
        double sin_theta, cos_theta;
        AxisAlignedBoundingBox m_box;
        bool m_has_box;
};

#endif