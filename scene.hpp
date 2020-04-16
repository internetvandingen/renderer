#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "shader.hpp"

class Scene {
private:
    const unsigned int W, H;
    sf::Uint8* pixels;
    Vector viewpoint;
    std::vector<Sphere*> sphereArray;
    std::vector<Light*> lightArray;
public:
    Scene(const unsigned int W, const unsigned int H, Vector viewpoint) : W(W), H(H), viewpoint(viewpoint) {
         this->pixels = new sf::Uint8[W*H*4];
    }

    void addObject(Sphere &sphere) {
        this->sphereArray.push_back(&sphere);
    }

    void addLight(Light &light) {
        this->lightArray.push_back(&light);
    }

    void updatePixels(){
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
    }

    double getPixel(int i, int j){
        Shape *shape = this->sphereArray[0];
        Light *light = this->lightArray[0];
        double w = (double)this->W;
        double h = (double)this->H;
        double value = 0.0;

        Vector pixelPoint(w/2-i, h/2-j, 800.0);
        Line pixelLine(this->viewpoint, pixelPoint);
        Vector* shapeIntersect = shape->intersect(pixelLine, false);
        if (shapeIntersect){
            // check if a lightsource can be seen from here
            Vector lightToIntersectDirection = shapeIntersect->subtract(light->getOrigin());
            Line lightToIntersect(light->getOrigin(), lightToIntersectDirection);
            Vector* possibleIntersectLight = shape->intersect(lightToIntersect, true);
            if (possibleIntersectLight == nullptr){
                value += shader(shape, shapeIntersect, light);
            }
            delete possibleIntersectLight;
        }
        delete shapeIntersect;

        return value;
    }

    sf::Uint8* getPixels() {
        return this->pixels;
    }
};

#endif
