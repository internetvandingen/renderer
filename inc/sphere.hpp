#ifndef __SPHERE_H_INCLUDED__
#define __SPHERE_H_INCLUDED__

#include "shape.hpp"
#include <math.h>

class Sphere : public Shape {
private:
    double radius;
public:
    Sphere(Vector origin, double diffuseCoefficient, double radius) : Shape(origin, diffuseCoefficient), radius(radius){};
    Vector getNormal(Vector impact);
    // returns how many of line.direction vectors you need to get to intersection with sphere, zero otherwise. (can not be negative)
    double intersect(Line line);
};



#endif
