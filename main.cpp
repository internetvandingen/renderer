#include <SFML/Graphics.hpp>

#include <iostream>

#include "vector.hpp"
#include "line.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "scene.hpp"

int main()
{
    const unsigned int W = 800;
    const unsigned int H = 600;

    sf::RenderWindow window(sf::VideoMode(W, H), "Renderer");
    window.setFramerateLimit(60);

    Vector viewpoint(0,0,0);
    Sphere sphere(Vector(0,0,1600), 0.5, 400.0);
    Light light(Vector(-800,400,800), 100.0);

    Scene scene(W, H, viewpoint);
    scene.addObject(sphere);
    scene.addLight(light);


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

        scene.updatePixels();
        texture.update(scene.getPixels());

        window.draw(sprite);
        window.display();
    }

    return 0;
}
