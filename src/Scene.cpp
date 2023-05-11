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

void Scene::intersect(Ray ray, HitRecord& hitRecord) {
    double distance = std::numeric_limits<double>::max();
    hitRecord.hit = false;
    
    for (auto object : sceneObjects) {
        HitRecord temp;
        if (object->intersect(ray, T_MIN, T_MAX, temp) && (temp.distance < distance)) {
            hitRecord.hit = true;
            hitRecord.distance = temp.distance;
            hitRecord.point = temp.point;
            hitRecord.normal = temp.normal;
            hitRecord.material = temp.material;
            distance = hitRecord.distance;
        }
    }
}
