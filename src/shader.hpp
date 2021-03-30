#ifndef __SHADER_H_INCLUDED__
#define __SHADER_H_INCLUDED__

#include "shape.hpp"
#include "vector"
#include "light.hpp"

class shader {
public:
    static double lambertian(Shape * shape, Vector &point, Light * light);
};

#endif
