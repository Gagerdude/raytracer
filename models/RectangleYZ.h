#ifndef RECTANGLEYZ_H
#define RECTANGLEYZ_H

#include "Model.h"

#include "Material.h"
#include "Ray.h"
#include "AxisAlignedBoundingBox.h"

class RectangleYZ: public Model{
    public:
        RectangleYZ();
        RectangleYZ(double _y_min, double _y_max, double _z_min, double _z_max, double _x, Material* m);

        ~RectangleYZ();

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        double y_min, y_max, z_min, z_max, x;

        Material* material;
};

#endif