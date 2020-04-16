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

    Vector* intersect(Line line, bool strict){
        // returns closest intersection of this object with line (closest to origin of line)
        Vector lineOriginToSphereOrigin = this->origin.subtract(line.getOrigin());
        Vector lineUnitDirection = line.getDirection().unit();

        Vector lineOrthogonalSphere = lineUnitDirection.multiply(lineOriginToSphereOrigin.dot(lineUnitDirection));
        Vector diff = lineOrthogonalSphere.subtract(lineOriginToSphereOrigin);
        if (diff.getLength() > this->radius){
            return nullptr;
        } else {
            double distanceOnProjection = sqrt(this->radius*this->radius - diff.getLength()*diff.getLength());
            Vector intersect = lineOrthogonalSphere.subtract(lineUnitDirection.multiply(distanceOnProjection));
            if (strict){
                // only return intersection if it lies on the vector
                if (intersect.getLength() < line.getLength() - 1e-8){
                    Vector temp = intersect.add(line.getOrigin());
                    return new Vector(temp.getX(), temp.getY(), temp.getZ(), temp.getLength());
                } else {
                    return nullptr;
                }
            } else {
                Vector temp = intersect.add(line.getOrigin());
                return new Vector(temp.getX(), temp.getY(), temp.getZ(), temp.getLength());
            }
        }
    }
};



#endif
