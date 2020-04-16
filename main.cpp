#include <SFML/Graphics.hpp>

#include <iostream>

#include "vector.hpp"
#include "line.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "light.hpp"

void trace(sf::Uint8* pixels, unsigned int W, unsigned int H, Vector viewpoint, Shape *shape, Light light);
double getPixel(int i, int j, double w, double h, Vector viewpoint, Shape *shape, Light light);
double shader(Shape *shape, Vector point, Light light);

int main()
{
    Sphere sphere(Vector(0,0,1600), 0.5, 400.0);
    Shape * p_sphere = &sphere;
    Vector viewpoint(0,0,0);

    Light light(Vector(-800,400,800), 100.0);

    const unsigned int W = 800;
    const unsigned int H = 600;

    sf::RenderWindow window(sf::VideoMode(W, H), "Renderer");
    window.setFramerateLimit(60);

    sf::Uint8* pixels = new sf::Uint8[W*H*4];

    sf::Texture texture;
    texture.create(W, H);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        trace(pixels, W, H, viewpoint, p_sphere, light);
        texture.update(pixels);

        window.draw(sprite);
        window.display();
    }

    return 0;
}

void trace(sf::Uint8* pixels, unsigned int W, unsigned int H, Vector viewpoint, Shape *shape, Light light){
    double* values = new double[(int)(W*H)];
    int maxIndex = 0;
    for (int i=0; i<(int)(W*H); i++){
        int y = i/W;
        int x = i%W;
        values[i] = getPixel(x, y, (double)W, (double)H, viewpoint, shape, light);
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

        pixels[i]   = value;
        pixels[i+1] = value;
        pixels[i+2] = value;
        pixels[i+3] = 255;
    }
}

double getPixel(int i, int j, double w, double h, Vector viewpoint, Shape *shape, Light light){
    double value = 0.0;
    Vector pixelPoint(w/2-i, h/2-j, 800.0);
    Line pixelLine(viewpoint, pixelPoint);
    Vector* intersect = shape->intersect(pixelLine, false);
    if (intersect){
        // check if a lightsource can be seen from here
        Vector lightToIntersectDirection = intersect->subtract(light.getOrigin());
        Line lightToIntersect(light.getOrigin(), lightToIntersectDirection);
        Vector* possibleIntersectLight = shape->intersect(lightToIntersect, true);
        if (possibleIntersectLight == nullptr){
            value += shader(shape, *intersect, light);
        }
        delete possibleIntersectLight;
    }
    delete intersect;

    return value;
}

double shader(Shape * shape, Vector point, Light light){
    Vector lightSource = light.getOrigin();
    Vector pointToLightSource = lightSource.subtract(point).unit();
    double dotproduct = shape->getNormal(point).dot(pointToLightSource);
    double brightness = shape->getDiffuseCoefficient() * light.getIntensity() * std::max(0.0, dotproduct);
    return brightness;
}

