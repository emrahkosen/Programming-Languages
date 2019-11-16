#include "Ray.h"
#include <iostream>
#include <cmath>
Ray::Ray()
{
}

Ray::Ray(const Vector3f& origin, const Vector3f& direction)
    : origin(origin)//, direction(direction)
{
  this->direction.x = direction.x/sqrtf(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);
  this->direction.y = direction.y/sqrtf(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);
  this->direction.z = direction.z/sqrtf(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);

}



Vector3f Ray::normalize(const Vector3f v) const
{
  Vector3f ret;
  ret.x = v.x/sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
  ret.y = v.y/sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
  ret.z = v.z/sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}



/* Takes a parameter t and returns the point accoring to t. t is the parametric variable in the ray equation o+t*d.*/
Vector3f Ray::getPoint(float t) const
{

   Vector3f ret;
   ret.x = origin.x + t*direction.x;
   ret.y = origin.y + t*direction.y;
   ret.z = origin.z + t*direction.z;
// std::cout<<"ret.  "<<ret.x<<"  "<<ret.y<<"  "<<ret.z<<std::endl;
   return ret;
}



/* Takes a point p and returns the parameter t according to p such that p = o+t*d. */
float Ray::gett(const Vector3f & p) const
{

   if(direction.x)
      return (p.x - origin.x)/direction.x;
  if(direction.y)
      return (p.y - origin.y)/direction.y;
  return (p.z -origin.z)/direction.z;
}
