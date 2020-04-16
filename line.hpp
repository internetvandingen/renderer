#ifndef __LINE_H_INCLUDED__
#define __LINE_H_INCLUDED__

/*
Line is made of two Vector objects: origin and direction
origin represents the point in space where the line starts (originates)
direction is the directional vector along which the line points
*/

class Line {
private:
    Vector origin, direction;
public:
    Line(Vector origin, Vector direction) : origin(origin), direction(direction) {}

    Vector getDirection(){
        return(this->direction);
    }

    Vector getOrigin(){
        return(this->origin);
    }

    double getLength(){
        return this->direction.getLength();
    }

};

#endif
