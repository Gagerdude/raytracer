#ifndef BOX_H
#define BOX_H

#include "Model.h"

#include "Material.h"
#include "Scene.h"

class Box: public Model{
    public:
        Box();
        Box(const vec3& min_corner, const vec3& max_corner, Material* material);
        ~Box();

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        vec3 m_min_corner, m_max_corner;
        Material* m_material;

        Scene* m_box_scene;
};

#endif