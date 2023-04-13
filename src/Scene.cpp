#include "Scene.hpp"
#include "constants.hpp"

Scene::Scene() {};

Scene::Scene(const Color& _ambientColor) : ambientColor(_ambientColor) {};

void Scene::addObject(Object* _object){
    sceneObjects.push_back(_object);
}

Object* Scene::operator [](const unsigned int i) {
    return sceneObjects.at(i);
}

int Scene::getNumObjects() {
    return (int) sceneObjects.size();
}

void Scene::addLight(Light *_light) {
    sceneLights.push_back(_light);
}

std::vector<Light*> Scene::lightSources() {
    return sceneLights;
}

Color Scene::getAmbientColor() {
    return ambientColor;
}

void Scene::setAmbientColor(Color _ambientColor) {
    ambientColor = _ambientColor;
}

bool Scene::intersect(Ray ray, HitRecord& hitRecord) const {
    double distance = std::numeric_limits<double>::max();
    HitRecord temp;
    bool hit;

    for (auto object : sceneObjects) {
        hit = object->intersect(ray, T_MIN, temp);
        if (hit && (temp.distance < distance)) {
            hitRecord = temp;
            distance = hitRecord.distance;
        }
    }

    return hit;
}
