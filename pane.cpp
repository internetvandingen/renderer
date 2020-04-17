#include "pane.hpp"

Pane::Pane(Vector origin, double diffuseCoefficient, Vector width, Vector height) :
    Shape(origin, diffuseCoefficient),
    width(width),
    height(height.subtract(width.unit().multiply(height.dot(width.unit())))),
    normal(this->width.cross(this->height).unit())
{
}


Vector Pane::getNormal(Vector impact) {
    return this->normal;
}

double Pane::intersect(Line line) {
    Vector lineOriginToPaneOrigin = this->origin.subtract(line.getOrigin());
    double linePortionOfD = -line.getDirection().dot(this->normal);
    if (linePortionOfD > 0) {
        double d = -lineOriginToPaneOrigin.dot(this->normal);
        double deltaW = line.getDirection().dot(this->width.unit());
        double w = d*deltaW/linePortionOfD;
        double deltaH = line.getDirection().dot(this->height.unit());
        double h = d*deltaH/linePortionOfD;

        double paneOriginToIntersectW = lineOriginToPaneOrigin.dot(this->width.unit())-w;
        double paneOriginToIntersectH = lineOriginToPaneOrigin.dot(this->height.unit())-h;
        if (std::abs(paneOriginToIntersectH) < this->height.getLength() &&
            std::abs(paneOriginToIntersectW) < this->width.getLength())
        {
            return sqrt(d*d+w*w+h*h)/line.getLength();
        }
    }
    return 0;
}
