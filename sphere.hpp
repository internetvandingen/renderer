#ifndef __SPHERE_H_INCLUDED__
#define __SPHERE_H_INCLUDED__

class Sphere : public Shape{
private:
    double radius;
public:
    Sphere(Vector origin, double diffuseCoefficient, double radius) : Shape(origin, diffuseCoefficient), radius(radius) {}

    Vector getNormal(Vector impact){
        return impact.subtract(this->origin).unit();
    }

    double intersect(Line line) {
        // returns how many of line.direction vectors you need to get to intersection with sphere, zero otherwise. (can not be negative)
        Vector lineOriginToSphereOrigin = this->origin.subtract(line.getOrigin());
        Vector lineUnitDirection = line.getDirection().unit();

        Vector lineOrthogonalSphere = lineUnitDirection.multiply(lineOriginToSphereOrigin.dot(lineUnitDirection));
        Vector diff = lineOrthogonalSphere.subtract(lineOriginToSphereOrigin);
        if (diff.getLength() > this->radius){
            return -1;
        } else {
            double distanceInSphere = sqrt(this->radius*this->radius - diff.getLength()*diff.getLength());
            double projectedDistance = lineOrthogonalSphere.getLength()-distanceInSphere;
            return projectedDistance/line.getLength();
        }
    }
};



#endif
