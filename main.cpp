#include <SFML/Graphics.hpp>

#include "pane.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "vector.hpp"


int main()
{
    const unsigned int W = 810;
    const unsigned int H = 610;

    sf::RenderWindow window(sf::VideoMode(W, H), "Renderer");
    window.setFramerateLimit(2);

    Vector viewpoint(400,0,0);
    // floor is on y(-400)
    double paneSize = 8000;
    Pane pane0(Vector(0,-400,2000), 0.5, Vector(paneSize,0,0), Vector(0,0,-paneSize));

    Sphere sphere0(Vector(0,0,1600), 0.5, 400.0);
    Sphere sphere1(Vector(-200,-200,1200), 0.5, 200.0);
    Light light0(Vector(-800,0,400), 100.0);
    Light light1(Vector(800,1600,400), 40.0);


    Scene scene(W, H, viewpoint);
    scene.addObject(sphere0);
    scene.addObject(sphere1);
    scene.addObject(pane0);
    scene.addLight(light0);
    scene.addLight(light1);

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
        viewpoint = viewpoint.add(Vector(-10,0,0));
        scene.updatePixels();
        texture.update(scene.getPixels());

        window.draw(sprite);
        window.display();
    }

    return 0;
}
