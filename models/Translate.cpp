#include "Translate.h"

Translate::Translate(Model* model, const vec3& offset){
    m_model = model;
    m_offset = offset;
}

Translate::~Translate(){
    delete m_model;
}

bool Translate::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    Ray translated(r.origin() - m_offset, r.direction(), r.time());

    if(m_model->hit(translated, t_min, t_max, rec)){
        rec.p += m_offset;
        return true;
    } else {
        return false;
    }
}

bool Translate::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    if(m_model->bounding_box(time_start, time_end, box)){
        box = AxisAlignedBoundingBox(box.min() + m_offset, box.max() + m_offset);
        return true;
    } else {
        return false;
    }
}
