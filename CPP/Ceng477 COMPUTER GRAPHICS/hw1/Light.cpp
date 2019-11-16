#include "Light.h"
#include <cmath>
#include <iostream>

/* Constructor. Implemented for you. */
PointLight::PointLight(const Vector3f & position, const Vector3f & intensity)
    : position(position), intensity(intensity)
{
}

// Compute the contribution of light at point p using the
// inverse square law formula
Vector3f PointLight::computeLightContribution(const Vector3f& p)
{
   Vector3f intensityAtP;

   float distanceSqrt = pow(position.x - p.x,2) + pow(position.y - p.y, 2) + pow(position.z - p.z, 2);

   if(distanceSqrt != 0)
   {

     intensityAtP.x = intensity.x/distanceSqrt;
     intensityAtP.y = intensity.y/distanceSqrt;
     intensityAtP.z = intensity.z/distanceSqrt;
  }
  else
  {
    intensityAtP.x = 0;
    intensityAtP.y = 0;
    intensityAtP.z = 0;
  }
  return intensityAtP;
}
