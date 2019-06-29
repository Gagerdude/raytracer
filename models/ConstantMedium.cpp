#include "ConstantMedium.h"

#include "Isotropic.h"
#include "Raytracer.h"

ConstantMedium::ConstantMedium(Model* boundary, double density, Texture* texture){
    m_boundary = boundary;
    m_density = density;
    m_phase_function = new Isotropic(texture);
}

ConstantMedium::~ConstantMedium(){
    delete m_boundary;
    delete m_phase_function;
}

bool ConstantMedium::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const{
    hit_record rec1, rec2;

    if(m_boundary->hit(r, std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(), rec1)){
        if(m_boundary->hit(r, rec1.t + 0.0001, std::numeric_limits<double>::max(), rec2)){
            if(rec1.t < t_min){
                rec1.t = t_min;
            }
            if(rec2.t > t_max){
                rec2.t = t_max;
            }
            if(rec1.t >= rec2.t){
                return false;
            }
            if(rec1.t < 0){
                rec1.t = 0;
            }

            double distance_inside_boundary = (rec2.t - rec1.t) * r.direction().length();
            
            std::uniform_real_distribution<double> dist(0,1);
            double hit_distance = -(1 / m_density) * std::log(dist(Raytracer::rng));

            if(hit_distance < distance_inside_boundary){
                rec.t = rec1.t + hit_distance / r.direction().length();
                rec.p = r.point_on_ray(rec.t);

                rec.normal = vec3(1,0,0);

                rec.material = m_phase_function;
                
                return true;
            }
        }
    }

    return false;
}

bool ConstantMedium::bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const{
    return m_boundary->bounding_box(time_start, time_end, box);
}
