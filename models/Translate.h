#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "Model.h"

class Translate: public Model{
    public:
        Translate(Model* model, const vec3& offset);
        ~Translate();
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        Model* m_model;
        vec3 m_offset;
};

#endif