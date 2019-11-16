#include "Shape.h"
#include "Scene.h"
#include <cstdio>
#include <cmath>

Shape::Shape(void)
{
}

Shape::Shape(int id, int matIndex)
    : id(id), matIndex(matIndex)
{}




/**********************************************************************************
***********************************************************************************
                               SPHERE CLASS
***********************************************************************************
***********************************************************************************/



Sphere::Sphere(void)
{}

/* Constructor for sphere. You will implement this. */
Sphere::Sphere(int id, int matIndex, int cIndex, float R)
    : Shape(id, matIndex),R(R),cIndex(cIndex)
{
}




float Sphere::dotProduct(const Vector3f a ,const Vector3f b) const
{    return a.x*b.x + a.y*b.y + a.z*b.z; }


float Sphere::toNorm(const Vector3f a) const
{  return sqrt(a.x*a.x + a.y*a.y + a.z*a.z); }







/* Sphere-ray intersection routine. You will implement this.
Note that ReturnVal structure should hold the information related to the intersection point,
e.g., coordinate of that point, normal at that point etc.
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */



ReturnVal Sphere::intersect(const Ray & ray) const
{
   ReturnVal ret;
   Vector3f Center = pScene->vertices[cIndex-1];



   Vector3f oc;
   oc.x = ray.origin.x - Center.x;
   oc.y = ray.origin.y - Center.y;
   oc.z = ray.origin.z - Center.z;

//  std::cout<<"oc.  "<<oc.x<<"  "<<oc.y<<"  "<<oc.z<<std::endl;

   float norm;


   float a = dotProduct(ray.direction,ray.direction);

   float b = 2.0*dotProduct(ray.direction,oc);
   float c = dotProduct(oc,oc) - R*R;
   float discriminant = b*b - 4*a*c;


   if(discriminant >= 0 && a != 0.0)
   {

     float tn = (-1.0*b -1.0*sqrt(discriminant))/(2.0*a);
     float tp = (-1.0*b +1.0*sqrt(discriminant))/(2.0*a);
     float t;





     ret.materialID = matIndex;
     ret.isInShape = true;
     if(tn < 0.0 && tp < 0.0)
        ret.isInShape = false;
     else if(tn > 0 && tp < 0)
     {
       t = tn;
     }
     else if(tn <= 0 && tp > 0)
     {
       t = tp;
     }
     else
      t = tn>tp?tp:tn;


     ret.intersectPoint = ray.getPoint(t);

     ret.Normal.x = ret.intersectPoint.x - Center.x;
     ret.Normal.y = ret.intersectPoint.y - Center.y;
     ret.Normal.z = ret.intersectPoint.z - Center.z;

     norm = toNorm(ret.Normal);//sqrtf(ret.Normal.x*ret.Normal.x + ret.Normal.y*ret.Normal.y + ret.Normal.z*ret.Normal.z);
     ret.Normal.x = ret.Normal.x/norm;//vektörü unit vektöre cevirk
     ret.Normal.y = ret.Normal.y/norm;
     ret.Normal.z = ret.Normal.z/norm;
     ret.type = 0;
     ret.id = id;


   }

   else
   {
     //ray ile küre kesişmiyor
     ret.isInShape = false;
   }

   return ret;
}



/**********************************************************************************
***********************************************************************************
                             TRIANGLE CLASS
***********************************************************************************
***********************************************************************************/
Triangle::Triangle(void)
{}

/* Constructor for triangle. You will implement this. */
Triangle::Triangle(int id, int matIndex, int p1Index, int p2Index, int p3Index)
    : Shape(id, matIndex),p1Index(p1Index),p2Index(p2Index),p3Index(p3Index)
{

}



Vector3f Triangle::crosProduct(const Vector3f a,const Vector3f b) const
{
  Vector3f ret;
  ret.x = a.y*b.z - a.z*b.y;
  ret.y = a.z*b.x - a.x*b.z;
  ret.z = a.x*b.y - a.y*b.x;
  float norm = sqrt(ret.x*ret.x + ret.y*ret.y + ret.z*ret.z);
  ret.x /= norm;
  ret.y /= norm;
  ret.z /= norm;
  return ret;

}

float Triangle::dotProduct(const Vector3f a ,const Vector3f b) const
{    return a.x*b.x + a.y*b.y + a.z*b.z; }


float Triangle::toNorm(const Vector3f a) const
{  return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z); }



float Triangle::determinant(float a0,float a1, float a2,
                            float b0,float b1, float b2,
                            float c0,float c1, float c2) const
{ return a0*(b1*c2-b2*c1)+b0*(a2*c1-a1*c2)+c0*(a1*b2-b1*a2); }



/* Triangle-ray intersection routine. You will implement this.
Note that ReturnVal structure should hold the information related to the intersection point,
e.g., coordinate of that point, normal at that point etc.
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */

ReturnVal Triangle::intersect(const Ray & ray) const
{

   ReturnVal ret;
   Vector3f A = pScene->vertices[p1Index-1];
   Vector3f B = pScene->vertices[p2Index-1];
   Vector3f C = pScene->vertices[p3Index-1];


   Vector3f ba;
   ba.x = B.x - A.x;
   ba.y = B.y - A.y;
   ba.z = B.z - A.z;

   Vector3f ca;
   ca.x = C.x - A.x;
   ca.y = C.y - A.y;
   ca.z = C.z - A.z;

//   Vector3f normal = crosProduct(ba,ca);

   float detA = determinant(A.x-B.x,A.x-C.x,ray.direction.x,
                            A.y-B.y,A.y-C.y,ray.direction.y,
                            A.z-B.z,A.z-C.z,ray.direction.z);

  if(detA == 0.0)
  {
    ret.isInShape = false;
    return ret;
  }


  float t = determinant(A.x-B.x,A.x-C.x,A.x-ray.origin.x,
                        A.y-B.y,A.y-C.y,A.y-ray.origin.y,
                        A.z-B.z,A.z-C.z,A.z-ray.origin.z);
  t /=  detA;

  if(t <= 0.0 )
  {
    ret.isInShape = false;
    return ret;
  }


  float GAMA = determinant(A.x-B.x,A.x-ray.origin.x,ray.direction.x,
                           A.y-B.y,A.y-ray.origin.y,ray.direction.y,
                           A.z-B.z,A.z-ray.origin.z,ray.direction.z);
  GAMA /= detA;
  if(GAMA < 0 || GAMA > 1)
  {
    ret.isInShape = false;
    return ret;
  }

  float BETA = determinant(A.x-ray.origin.x,A.x-C.x,ray.direction.x,
                                 A.y-ray.origin.y,A.y-C.y,ray.direction.y,
                                 A.z-ray.origin.z,A.z-C.z,ray.direction.z);
  BETA /= detA;

  if(BETA < 0 || BETA > 1)
  {
    ret.isInShape = false;
    return ret;
  }

  if(BETA + GAMA > 1)
  {
    ret.isInShape = false;
    return ret;
  }


//std::cout<<"point is in a triangle "<<std::endl;
  ret.isInShape = true;
  ret.Normal = crosProduct(ba,ca);

  ret.Normal.x = ret.Normal.x/toNorm(ret.Normal);
  ret.Normal.y = ret.Normal.y/toNorm(ret.Normal);
  ret.Normal.z = ret.Normal.z/toNorm(ret.Normal);
  ret.intersectPoint = ray.getPoint(t);
  // ret.intersectPoint.x = ray.origin.x + ray.origin.x*t;
  // ret.intersectPoint.y = ray.origin.y + ray.origin.y*t;
  // ret.intersectPoint.z = ray.origin.z + ray.origin.z*t;
  ret.materialID = matIndex;
  ret.type = 1;
  ret.id = id;


  return ret;
}





/**********************************************************************************
***********************************************************************************
                             MESH CLASS
***********************************************************************************
***********************************************************************************/



Mesh::Mesh()
{}

/* Constructor for mesh. You will implement this. */
Mesh::Mesh(int id, int matIndex, const vector<Triangle>& faces)
    : Shape(id, matIndex),faces(faces)
{
   // //for (auto& it : faces)
   // int len = faces.size();
   // for(int i = 0; i< len ; i++)
   // {
   //   this->faces.push_back(faces[i]);
   // }
}

float Mesh::dotProduct(const Vector3f a,const Vector3f b) const
{    return a.x*b.x + a.y*b.y + a.z*b.z; }






/* Mesh-ray intersection routine. You will implement this.
Note that ReturnVal structure should hold the information related to the intersection point,
e.g., coordinate of that point, normal at that point etc.
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */
ReturnVal Mesh::intersect(const Ray & ray) const
{
   ReturnVal working;
   int minTriangle = -1;
   float distanceOfPointToRay = 99999999;//ray origin ile içinden geçtiği trianglelerden en yalını bulacagız
   int sizeOfFaces= faces.size();


   for(int i = 0; i < sizeOfFaces; i++ )
   {

     working = faces[i].intersect(ray);


     if(working.isInShape == true)
     {

       float length = (ray.origin.x-working.intersectPoint.x)*(ray.origin.x-working.intersectPoint.x) +
                      (ray.origin.y-working.intersectPoint.y)*(ray.origin.y-working.intersectPoint.y) +
                      (ray.origin.z-working.intersectPoint.z)*(ray.origin.z-working.intersectPoint.z);

       //dotProduct(ray.origin, working.intersectPoint);
      if(length < distanceOfPointToRay )
      {
             minTriangle = i;
             distanceOfPointToRay = length;
      }
     }
   }
   if(minTriangle ==  -1)
   {
      working.isInShape = false;
      return working;
   }
   else
   {
       working = faces[minTriangle].intersect(ray);
       working.id = id;
       return working;
   }

}
