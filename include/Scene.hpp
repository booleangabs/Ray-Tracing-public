#ifndef SCENE_H
#define SCENE_H

#include "Vec3.hpp"
#include "Point3.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Image.hpp"

class Scene{

    public:
        Scene(Vec3 background, Color* ambientcolor);
        void setObject(Object* actualObjetic); //Seta o objeto na cena atual
        //Funcoes pra o traço de luz e interseçao
    private:
        Color *ambientcolor;
        Vec3 background;
        vector<*Object> sceneObject;
        //Algum metodo de iluminaçao escolhido(trabalha junto com o traço)

};


#endif
