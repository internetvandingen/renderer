#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include "vector.hpp"
#include "shape.hpp"
#include "light.hpp"
#include "shader.hpp"

class Scene {
private:
    const unsigned int W, H;
    sf::Uint8* pixels;
    Vector* viewpoint;
    std::vector<Shape*> shapeArray;
    std::vector<Light*> lightArray;
public:
    Scene(const unsigned int W, const unsigned int H, Vector &viewpoint);

    void addObject(Shape &shape);
    void addLight(Light &light);

    void updatePixels();
    double getPixel(int i, int j);


    sf::Uint8* getPixels() {
        return this->pixels;
    }
};

#endif
