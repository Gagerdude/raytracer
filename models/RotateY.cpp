#include "RotateY.h"

RotateY::RotateY(Model* model, double theta){
    double theta_radians = (M_PI / 180.0) * theta;
    cos_theta = std::cos(theta_radians);
    sin_theta = std::sin(theta_radians);

    m_model = model;

    m_has_box = m_model->bounding_box(0, 1, m_box);

    vec3 min(std::numeric_limits<double>::max());
    vec3 max(std::numeric_limits<double>::lowest());

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                double x = i * m_box.max().x() + (1 - i) * m_box.min().x();
                double y = j * m_box.max().y() + (1 - j) * m_box.min().y();
                double z = k * m_box.max().z() + (1 - k) * m_box.min().z();

                double x_prime = cos_theta * x + sin_theta * z;
                double z_prime = -sin_theta * x + cos_theta * z;

                vec3 vec(x_prime, y, z_prime);

                for(int c = 0; c < 3; c++){
                    if(vec[c] > max[c]){
                        max[c] = vec[c];
                    }
                    if(vec[c] < min[c]){
                        min[c] = vec[c];
                    }
                }
            }
        }
    }

    m_box = AxisAlignedBoundingBox(min, max);
}

RotateY::~RotateY(){
    delete m_model;
}

bool RotateY::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    vec3 origin = r.origin();
    vec3 direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta * r.direction()[2];

    Ray rotated(origin, direction, r.time());

    if(m_model->hit(rotated, t_min, t_max, rec)){
        rec.p = vec3(
            cos_theta * rec.p[0] + sin_theta * rec.p[2],
            rec.p[1],
            -sin_theta * rec.p[0] + cos_theta * rec.p[2]
        );
        rec.normal = vec3(
            cos_theta * rec.normal[0] + sin_theta * rec.normal[2],
            rec.normal[1],
            -sin_theta * rec.normal[0] + cos_theta * rec.normal[2]
        );

        return true;
    } else {
        return false;
    }
}

bool RotateY::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    box = m_box;
    return m_has_box;
}
