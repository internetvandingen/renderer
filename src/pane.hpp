#ifndef __PANE_H_INCLUDED__
#define __PANE_H_INCLUDED__

#include "vector.hpp"
#include "line.hpp"
#include "shape.hpp"

class Pane : public Shape {
private:
    Vector width, height, normal;
public:
    // Constructors pane spanned by width and height, with size: length(width) by length(part of height perpendicular to width)
    // pane is position with its center at given vector origin.
    // The normal vector of the plane is defined by (width cross height), and it is only visible from the side which has the normal pointing out
    Pane(Vector origin, double diffuseCoefficient, Vector width, Vector height);
    Vector getNormal(Vector impact);
    double intersect(Line line);
};


#endif
