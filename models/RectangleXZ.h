#ifndef RECTANGLEXZ_H
#define RECTANGLEXZ_H

#include "Model.h"

#include "Material.h"
#include "Ray.h"
#include "AxisAlignedBoundingBox.h"

class RectangleXZ: public Model{
    public:
        RectangleXZ();
        RectangleXZ(double _x_min, double _x_max, double _z_min, double _z_max, double _y, Material* m);

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        double x_min, x_max, z_min, z_max, y;

        Material* material;
};

#endif