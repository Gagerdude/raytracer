#ifndef SCENE_H
#define SCENE_H

#include "Model.h"

#include "Ray.h"
#include "AxisAlignedBoundingBox.h"

class Scene: public Model{
    public:
        Scene(Model** models, int num_models);
        ~Scene();

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const;
        virtual bool bounding_box(double time_start, double time_end, AxisAlignedBoundingBox& box) const;

    private:
        Model** scene;
        int scene_size;
};

#endif