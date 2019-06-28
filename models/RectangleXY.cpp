#include "RectangleXY.h"

RectangleXY::RectangleXY(){

}

RectangleXY::RectangleXY(double _x_min, double _x_max, double _y_min, double _y_max, double _z, Material* m){
    x_min = _x_min;
    x_max = _x_max;
    y_min = _y_min;
    y_max = _y_max;
    z = _z;

    material = m;
}

bool RectangleXY::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    double t = (z - r.origin().z()) / r.direction().z();

    if(t < t_min || t > t_max){
        return false;
    }

    double x = r.origin().x() + t * r.direction().x();
    double y = r.origin().y() + t * r.direction().y();

    if(x < x_min || x > x_max || y < y_min || y > y_max){
        return false;
    }

    rec.t = t;
    rec.p = r.point_on_ray(t);
    rec.normal = vec3(0, 0, 1);
    rec.material = material;

    rec.u = (x - x_min) / (x_max - x_min);
    rec.v = (y - y_min) / (y_max - y_min);

    if(dot(rec.normal, r.direction()) > 0){
        rec.normal = vec3(0, 0, -1);
    }

    return true;
}

bool RectangleXY::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    box = AxisAlignedBoundingBox(vec3(x_min, y_min, z - .0001), vec3(x_max, y_max, z + .0001));
    return true;
}
