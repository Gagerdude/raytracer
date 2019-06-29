#ifndef CONSTANTMEDIUM_H
#define CONSTANTMEDIUM_H

#include "Model.h"

#include "Texture.h"
#include "Material.h"

class ConstantMedium: public Model{
    public:
        ConstantMedium(Model* boundary, double density, Texture* texture);
        ~ConstantMedium();
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        Model* m_boundary;
        double m_density;
        Material* m_phase_function;
};

#endif