#ifndef SCENE_H
#define SCENE_H

#include "Material.hpp"
#include "Object.hpp"
#include "HitRecord.hpp"
#include <vector>
#include <limits>

#define T_MIN 1e-5

class Scene{
    private:
        Color ambientColor;
        std::vector<Object*> sceneObjects;
        
    public:
        Scene();
        Scene(const Color& _ambientColor);

        void addObject(Object* _object);
        Object* operator [](const unsigned int i);
        int getNumObjects();

        Color getAmbientColor();
        void setAmbientColor(Color _ambientColor);

        bool intersect(Ray ray, HitRecord& hitRecord) const;
};

#endif
