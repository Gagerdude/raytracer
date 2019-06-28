#include "RectangleXZ.h"

RectangleXZ::RectangleXZ(){

}

RectangleXZ::RectangleXZ(double _x_min, double _x_max, double _z_min, double _z_max, double _y, Material* m){
    x_min = _x_min;
    x_max = _x_max;
    z_min = _z_min;
    z_max = _z_max;
    y = _y;

    material = m;
}

bool RectangleXZ::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    double t = (y - r.origin().y()) / r.direction().y();

    if(t < t_min || t > t_max){
        return false;
    }

    double x = r.origin().x() + t * r.direction().x();
    double z = r.origin().z() + t * r.direction().z();

    if(x < x_min || x > x_max || z < z_min || z > z_max){
        return false;
    }

    rec.t = t;
    rec.p = r.point_on_ray(t);
    rec.normal = vec3(0, 1, 0);
    rec.material = material;

    rec.u = (x - x_min) / (x_max - x_min);
    rec.v = (z - z_min) / (z_max - z_min);

    if(dot(rec.normal, r.direction()) > 0){
        rec.normal = vec3(0, -1, 0);
    }

    return true;
}

bool RectangleXZ::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    box = AxisAlignedBoundingBox(vec3(x_min, y - .0001, z_min), vec3(x_max, y + .0001, z_max));
    return true;
}
