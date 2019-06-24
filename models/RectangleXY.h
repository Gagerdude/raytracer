#ifndef RECTANGLEXY_H
#define RECTANGLEXY_H

#include "Model.h"

#include "Material.h"
#include "Ray.h"
#include "AxisAlignedBoundingBox.h"

class RectangleXY: public Model{
    public:
        RectangleXY();
        RectangleXY(double _x_min, double _x_max, double _y_min, double _y_max, double _z, Material* m);

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        double x_min, x_max, y_min, y_max, z;

        Material* material;
};

#endif