#ifndef SCENE_H
#define SCENE_H

#include "Material.hpp"
#include "Object.hpp"
#include "HitRecord.hpp"
#include "Light.hpp"
#include <vector>
#include <limits>

class Scene{
    private:
        Color ambientColor;
        std::vector<Object*> sceneObjects;
        std::vector<Light*> sceneLights;
        
    public:
        Scene();
        Scene(const Color& _ambientColor);

        void addObject(Object* _object);
        Object* operator [](const unsigned int i);
        int getNumObjects();

        void addLight(Light* _light);
        std::vector<Light*> lightSources();

        Color getAmbientColor();
        void setAmbientColor(Color _ambientColor);

        bool intersect(Ray ray, HitRecord& hitRecord) const;
};

#endif
