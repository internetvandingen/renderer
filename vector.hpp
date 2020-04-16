#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__

#include <iostream>
#include <math.h>

/*
Vector is made of three numbers: one for each coordinte x,y,z
It can represent either a direction or a point in space
*/

class Vector {
private:
    double x, y, z, length;
public:
    Vector(double x, double y, double z);
    Vector(double x, double y, double z, double length);
    Vector add(Vector other);
    Vector multiply(double number);
    Vector subtract(Vector other);
    double dot(Vector other);
    Vector unit();
    Vector copy();
    double getX();
    double getY();
    double getZ();
    double getLength();
    friend std::ostream& operator<<(std::ostream& os, Vector vec);
};

#endif
