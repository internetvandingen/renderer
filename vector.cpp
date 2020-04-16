#include "vector.hpp"

std::ostream& operator<<(std::ostream& os, Vector vec){
    os << '(' << vec.getX() << ',' << vec.getY() << ',' << vec.getZ() << ')' << '\n';
    return os;
}

Vector Vector::copy(){
    return Vector(this->getX(), this->getY(), this->getZ(), this->getLength());
}

// constructors
Vector::Vector(double x, double y, double z) : x(x), y(y), z(z), length(sqrt(x*x+y*y+z*z)) {}
Vector::Vector(double x, double y, double z, double length) : x(x), y(y), z(z), length(length){}

Vector Vector::add(Vector other){
    return Vector(this->x+other.getX(), this->y+other.getY(), this->z+other.getZ());
}

Vector Vector::multiply(double number){
    return Vector(this->x*number, this->y*number, this->z*number, this->length*number);
}

Vector Vector::subtract(Vector other){
    return Vector(this->x-other.getX(), this->y-other.getY(), this->z-other.getZ());
}

double Vector::dot(Vector other){
    return this->x*other.getX() + this->y*other.getY() + this->z*other.getZ();
}

Vector Vector::unit(){
    return Vector(this->x/this->length, this->y/this->length, this->z/this->length, 1.0);
}

double Vector::getX(){return(this->x);}
double Vector::getY(){return(this->y);}
double Vector::getZ(){return(this->z);}
double Vector::getLength(){return(this->length);}
