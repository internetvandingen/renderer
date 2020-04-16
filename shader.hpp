#ifndef __SHADER_H_INCLUDED__
#define __SHADER_H_INCLUDED__

double shader(Shape * shape, Vector * point, Light * light){
    Vector lightSource = light->getOrigin();
    Vector pointToLightSource = lightSource.subtract(*point).unit();
    double dotproduct = shape->getNormal(*point).dot(pointToLightSource);
    double brightness = shape->getDiffuseCoefficient() * light->getIntensity() * std::max(0.0, dotproduct);
    return brightness;
}

#endif
