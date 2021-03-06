#include "scene.hpp"

Scene::Scene(const unsigned int W, const unsigned int H, Vector &viewpoint) : W(W), H(H), viewpoint(&viewpoint) {
     this->pixels = new sf::Uint8[W*H*4];
}

void Scene::addObject(Shape &shape) {
    this->shapeArray.push_back(&shape);
}

void Scene::addLight(Light &light) {
    this->lightArray.push_back(&light);
}

void Scene::updatePixels(){
    unsigned int W = this->W;
    unsigned int H = this->H;

    double* values = new double[(int)(W*H)];
    int maxIndex = 0;
    for (int i=0; i<(int)(W*H); i++){
        int y = i/W;
        int x = i%W;
        values[i] = this->getPixel(x, y);
        if(values[i] > values[maxIndex]){
            maxIndex = i;
        }
    }
    double maximum = values[maxIndex];

    for(register unsigned int i = 0; i < W*H*4; i += 4) {
        // R G B A values, 8 bit unsigned int (0-255)
        // RGB: 0 black, 255 white; A: 0 transparant, 255 solid
        int index = i/4;
        sf::Uint8 value = 255*values[index]/maximum;

        this->pixels[i]   = value;
        this->pixels[i+1] = value;
        this->pixels[i+2] = value;
        this->pixels[i+3] = 255;
    }
    delete values;
}

double Scene::getPixel(int i, int j){
    double w = (double)this->W;
    double h = (double)this->H;
    double value = 0.0;

    Vector pixelPoint(w/2-i, h/2-j, 800.0);
    Line pixelLine(*this->viewpoint, pixelPoint);

    Shape * shape;
    bool hasIntersect = false;
    double shapeIntersect = std::numeric_limits<double>::max();
    for (Shape* const& tempShape: this->shapeArray) {
        double tempShapeIntersect = tempShape->intersect(pixelLine);
        if (tempShapeIntersect > 0 && tempShapeIntersect < shapeIntersect) {
            shapeIntersect = tempShapeIntersect;
            shape = tempShape;
            hasIntersect = true;
        }
    }

    if (hasIntersect){
        // check if a lightsource can be seen from here
        Vector toShapeIntersect = pixelLine.getOrigin().add(pixelLine.getDirection().multiply(shapeIntersect));

        for (Light* const& tempLight: this->lightArray) {
            Vector lightToIntersectDirection = toShapeIntersect.subtract(tempLight->getOrigin());
            Line lightToIntersect(tempLight->getOrigin(), lightToIntersectDirection);
            bool blocked = false;
            for (Shape* const& tempShape: this->shapeArray) {
                if (tempShape == shape) {
                    continue;
                }
                double possibleIntersectLight = tempShape->intersect(lightToIntersect);
                if (possibleIntersectLight > 0 && possibleIntersectLight < 1){
                    blocked = true;
                    break;
                }
            }
            if (!blocked) {
                value += shader::lambertian(shape, toShapeIntersect, tempLight);
            }
        }
    }

    return value;
}
