#include "Box.h"

#include "RectangleXY.h"
#include "RectangleXZ.h"
#include "RectangleYZ.h"

#include "Wrapper.h"

Box::Box(){

}

Box::Box(const vec3& min_corner, const vec3& max_corner, Material* material){
    m_min_corner = min_corner;
    m_max_corner = max_corner;

    m_material = material;

    Model** m_box = new Model*[6];

    m_box[0] = new RectangleXY(m_min_corner.x(), m_max_corner.x(), m_min_corner.y(), m_max_corner.y(), m_min_corner.z(), new Wrapper(m_material));
    m_box[1] = new RectangleXY(m_min_corner.x(), m_max_corner.x(), m_min_corner.y(), m_max_corner.y(), m_max_corner.z(), new Wrapper(m_material));
    m_box[2] = new RectangleXZ(m_min_corner.x(), m_max_corner.x(), m_min_corner.z(), m_max_corner.z(), m_min_corner.y(), new Wrapper(m_material));
    m_box[3] = new RectangleXZ(m_min_corner.x(), m_max_corner.x(), m_min_corner.z(), m_max_corner.z(), m_max_corner.y(), new Wrapper(m_material));
    m_box[4] = new RectangleYZ(m_min_corner.y(), m_max_corner.y(), m_min_corner.z(), m_max_corner.z(), m_min_corner.x(), new Wrapper(m_material));
    m_box[5] = new RectangleYZ(m_min_corner.y(), m_max_corner.y(), m_min_corner.z(), m_max_corner.z(), m_max_corner.x(), new Wrapper(m_material));

    m_box_scene = new Scene(m_box, 6);

    delete[] m_box;
}

Box::~Box(){
    delete m_box_scene;
    delete m_material;
}

bool Box::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    return m_box_scene->hit(r, t_min, t_max, rec);
}

bool Box::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    box = AxisAlignedBoundingBox(m_min_corner, m_max_corner);
    return true;
}
