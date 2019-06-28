#include "RectangleYZ.h"

RectangleYZ::RectangleYZ(){

}

RectangleYZ::RectangleYZ(double _y_min, double _y_max, double _z_min, double _z_max, double _x, Material* m){
    y_min = _y_min;
    y_max = _y_max;
    z_min = _z_min;
    z_max = _z_max;
    x = _x;

    material = m;
}

RectangleYZ::~RectangleYZ(){
    delete material;
}

bool RectangleYZ::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    double t = (x - r.origin().x()) / r.direction().x();

    if(t < t_min || t > t_max){
        return false;
    }

    double y = r.origin().y() + t * r.direction().y();
    double z = r.origin().z() + t * r.direction().z();

    if(y < y_min || y > y_max || z < z_min || z > z_max){
        return false;
    }

    rec.t = t;
    rec.p = r.point_on_ray(t);
    rec.normal = vec3(1, 0, 0);
    rec.material = material;

    rec.u = (y - y_min) / (y_max - y_min);
    rec.v = (z - z_min) / (z_max - z_min);

    if(dot(rec.normal, r.direction()) > 0){
        rec.normal = vec3(-1, 0, 0);
    }

    return true;
}

bool RectangleYZ::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    box = AxisAlignedBoundingBox(vec3(x - .0001, y_min, z_min), vec3(x + .0001, y_max, z_max));
    return true;
}
