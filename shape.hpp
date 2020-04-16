#ifndef __SHAPE_H_INCLUDED__
#define __SHAPE_H_INCLUDED__

class Shape {
protected:
    double diffuseCoefficient;
    Vector origin;
public:
    Shape(Vector origin, double diffuseCoefficient) : diffuseCoefficient(diffuseCoefficient), origin(origin) {}

    virtual Vector getNormal(Vector impact) = 0;

    virtual double intersect(Line line) = 0;

    double getDiffuseCoefficient(){
        return(this->diffuseCoefficient);
    }
};

#endif
