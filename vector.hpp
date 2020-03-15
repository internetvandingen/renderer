#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__

/*
Vector is made of three numbers: one for each coordinte x,y,z
It can represent either a direction or a point in space
*/

class Vector {
private:
    const double x, y, z, length;
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

std::ostream& operator<<(std::ostream& os, Vector vec){
    os << '(' << vec.getX() << ',' << vec.getY() << ',' << vec.getZ() << ')' << '\n';
    return os;
}

Vector Vector::copy(){
    Vector objCopy(this->getX(), this->getY(), this->getZ(), this->getLength());
    return objCopy;
}

// constructors
Vector::Vector(double x, double y, double z) : x(x), y(y), z(z), length(sqrt(x*x+y*y+z*z)) {}
Vector::Vector(double x, double y, double z, double length) : x(x), y(y), z(z), length(length){}

Vector Vector::add(Vector other){
    Vector result(this->x+other.getX(), this->y+other.getY(), this->z+other.getZ());
    return result;
}

Vector Vector::multiply(double number){
    Vector result(this->x*number, this->y*number, this->z*number, this->length*number);
    return result;
}

Vector Vector::subtract(Vector other){
    Vector result(this->x-other.getX(), this->y-other.getY(), this->z-other.getZ());
    return result;
}

double Vector::dot(Vector other){
    return this->x*other.getX() + this->y*other.getY() + this->z*other.getZ();
}

Vector Vector::unit(){
    Vector result(this->x/this->length, this->y/this->length, this->z/this->length, 1.0);
    return result;
}

double Vector::getX(){return(this->x);}
double Vector::getY(){return(this->y);}
double Vector::getZ(){return(this->z);}
double Vector::getLength(){return(this->length);}


#endif
