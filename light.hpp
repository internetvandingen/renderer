#ifndef __LIGHT_H_INCLUDED__
#define __LIGHT_H_INCLUDED__

/*

*/

class Light {
private:
    //int direction;
    Vector origin;
    double intensity;
public:
    //Vector origin, Vector direction
    Light(Vector origin, double intensity) : origin(origin), intensity(intensity) {}

    Vector getOrigin(){
        return(this->origin);
    }

    double getIntensity(){
        return this->intensity;
    }

};

#endif
