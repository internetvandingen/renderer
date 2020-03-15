#include <SFML/Graphics.hpp>

#include <iostream>

#include "vector.hpp"
#include "line.hpp"
#include "sphere.hpp"
#include "light.hpp"

#include <math.h>


double getPixel(int i, int j, double w, double h, Vector viewpoint, Sphere sphere, Light light);
void trace(sf::Uint8* pixels, unsigned int W, unsigned int H, Vector viewpoint, Sphere sphere, Light light);
double shader(Sphere sphere, Vector point, Light light);

int main()
{
    Vector sphereOrigin(0,0,1600);
    Sphere sphere(sphereOrigin, 400.0, 0.2);

    Vector viewpoint(0,0,0);

    Vector lightOrigin(-800,0,800);
    Light light(lightOrigin, 100.0);

    const unsigned int W = 800;
    const unsigned int H = 600; // you can change this to full window size later

    sf::RenderWindow window(sf::VideoMode(W, H), "Renderer");
    window.setFramerateLimit(30);

    sf::Uint8* pixels = new sf::Uint8[W*H*4];

    sf::Uint8 value = 150;
    for(register unsigned int i = 0; i < W*H*4; i += 4) {
        // R G B A values, 8 bit unsigned int (0-255)
        // RGB: 0 black, 255 white; A: 0 transparant, 255 solid
        pixels[i]   = value;
        pixels[i+1] = value;
        pixels[i+2] = value;
        pixels[i+3] = 255;
    }

    sf::Texture texture;
    texture.create(W, H);


        sf::Sprite sprite(texture); // needed to draw the texture on screen

        trace(pixels, W, H, viewpoint, sphere, light);
        texture.update(pixels);

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

double getPixel(int i, int j, double w, double h, Vector viewpoint, Sphere sphere, Light light){
    double value = 0.0;
    Vector pixelPoint(w/2-i, h/2-j, 800.0);
    Line pixelLine(viewpoint, pixelPoint);
    Vector* intersect = sphere.intersect(pixelLine, false);
    if (intersect){
        // check if a lightsource can be seen from here
        Vector lightToIntersectDirection = intersect->subtract(light.getOrigin());
        Line lightToIntersect(light.getOrigin(), lightToIntersectDirection);
        Vector* possibleIntersectLight = sphere.intersect(lightToIntersect, true);
        if (possibleIntersectLight == nullptr){
            value += shader(sphere, *intersect, light);
        }
        delete possibleIntersectLight;
    }
    delete intersect;

    return value;
}

void trace(sf::Uint8* pixels, unsigned int W, unsigned int H, Vector viewpoint, Sphere sphere, Light light){
    double* values = new double[(int)(W*H)];
    int maxIndex = 0;
    for (int i=0; i<(int)(W*H); i++){
        int y = i/W;
        int x = i%W;
        values[i] = getPixel(x, y, (double)W, (double)H, viewpoint, sphere, light);
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

double shader(Sphere sphere, Vector point, Light light){
    Vector lightSource = light.getOrigin();
    Vector pointToLightSource = lightSource.subtract(point).unit();
    double dotproduct = sphere.getNormal(point).dot(pointToLightSource);
    double brightness = sphere.getDiffuseCoefficient() * light.getIntensity() * std::max(0.0, dotproduct);
    return brightness;
}

