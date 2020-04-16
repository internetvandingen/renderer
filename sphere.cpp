#include "sphere.hpp"

Vector Sphere::getNormal(Vector impact){
    return impact.subtract(this->origin).unit();
}

double Sphere::intersect(Line line) {
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
