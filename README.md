# Renderer
Render simple objects with ray tracing.
Currently, the following objects can be drawn on screen:
- sphere
- rectangular pane
- cube (multiple panes)

More detailed information can be found on [lennartknoll.nl/ray-tracing](https://lennartknoll.nl/ray-tracing/).


## What is ray tracing?
Ray tracing is a technique to render physical objects (e.g. a sphere) to an image. It simulates rays of light and their interactions with objects.

![schematic](https://lennartknoll.nl/wp-content/uploads/2020/04/raytracing_schematic.png)

Light that hits the camera is traced back to the objects they scattered from.
Example image output of scene with 2 spheres on a flat surface with 2 light sources behind the camera, one on the right and a weaker one on the left.

![example_output](https://lennartknoll.nl/wp-content/uploads/2020/05/frame54.png)

## Dependencies
Use of external libraries is minimized: pixels are individually written to the screen.
- [SFML](https://www.sfml-dev.org/) 2.5
