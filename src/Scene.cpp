#include "Scene.hpp"
#include "Color.hpp"
#include "HitRecord.hpp"
#include "Object.hpp"
#include <limits>
#include <vector>
#include <memory>

Scene::Scene(Vec3 background, Color* ambientcolor){

    this->background = background;
    this->ambientcolor = ambientcolor;
}

void Scene::setObject(Object* actualObjetic){

    this->sceneObject.push_back(actualObjetic);
}


