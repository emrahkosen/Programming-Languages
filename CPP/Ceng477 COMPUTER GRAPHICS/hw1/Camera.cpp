#include "Camera.h"
#include <iostream>
#include <cmath>

Camera::Camera(int id,                      // Id of the camera
               const char* imageName,       // Name of the output PPM file
               const Vector3f& pos,         // Camera position
               const Vector3f& gaze,        // Camera gaze direction
               const Vector3f& up,          // Camera up direction
               const ImagePlane& imgPlane)  // Image plane parameters
{
   this->id = id;
   for(int i = 0; imageName[i] != '\0'; i++)
   {
     this->imageName[i] = imageName[i];
     this->imageName[i+1] = '\0';

   }


   this->imgPlane = imgPlane;
   this->cameraPosition = pos;
//   this->cameraGazeVector = gaze;//unit vector al
   this->cameraGazeVector.x = gaze.x/sqrtf(gaze.x*gaze.x + gaze.y*gaze.y + gaze.z*gaze.z);
   this->cameraGazeVector.y = gaze.y/sqrtf(gaze.x*gaze.x + gaze.y*gaze.y + gaze.z*gaze.z);
   this->cameraGazeVector.z = gaze.z/sqrtf(gaze.x*gaze.x + gaze.y*gaze.y + gaze.z*gaze.z);



  // this->cameraU = up;//unit vector al
   this->cameraU.x = this->cameraGazeVector.y*up.z - this->cameraGazeVector.z*up.y;
   this->cameraU.y = this->cameraGazeVector.z*up.x - this->cameraGazeVector.x*up.z;
   this->cameraU.z = this->cameraGazeVector.x*up.y - this->cameraGazeVector.y*up.x;

   this->cameraU.x = this->cameraU.x/sqrtf(this->cameraU.x*this->cameraU.x + this->cameraU.y*this->cameraU.y + this->cameraU.z*this->cameraU.z);
   this->cameraU.y = this->cameraU.y/sqrtf(this->cameraU.x*this->cameraU.x + this->cameraU.y*this->cameraU.y + this->cameraU.z*this->cameraU.z);
   this->cameraU.z = this->cameraU.z/sqrtf(this->cameraU.x*this->cameraU.x + this->cameraU.y*this->cameraU.y + this->cameraU.z*this->cameraU.z);


   this->cameraV.x = up.x;//this->cameraGazeVector.y*this->cameraU.z + this->cameraGazeVector.z*this->cameraU.y;
   this->cameraV.y = up.y;//this->cameraGazeVector.z*this->cameraU.x + this->cameraGazeVector.x*this->cameraU.z;
   this->cameraV.z = up.z;//this->cameraGazeVector.x*this->cameraU.y + this->cameraGazeVector.y*this->cameraU.x;

   this->cameraV.x = this->cameraV.x/sqrtf(this->cameraV.x*this->cameraV.x + this->cameraV.y*this->cameraV.y + this->cameraV.z*this->cameraV.z);
   this->cameraV.y = this->cameraV.y/sqrtf(this->cameraV.x*this->cameraV.x + this->cameraV.y*this->cameraV.y + this->cameraV.z*this->cameraV.z);
   this->cameraV.z = this->cameraV.z/sqrtf(this->cameraV.x*this->cameraV.x + this->cameraV.y*this->cameraV.y + this->cameraV.z*this->cameraV.z);


}







Vector3f Camera::normalize(const Vector3f v) const
{
  Vector3f ret;
  ret.x = v.x/sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
  ret.y = v.y/sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
  ret.z = v.z/sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

/* Takes coordinate of an image pixel as row and col, and
 * returns the ray going through that pixel.
 */


Ray Camera::getPrimaryRay(int row, int col) const
{

   float su = (imgPlane.right - imgPlane.left )*(row + 0.5)/(1.0*imgPlane.nx);
   float sv = (imgPlane.top - imgPlane.bottom )*(col + 0.5)/(1.0*imgPlane.ny);
   Vector3f m;                      //m gaze vektor plane yi hangi noktada kesiyor
   m.x = cameraPosition.x + cameraGazeVector.x*imgPlane.distance;
   m.y = cameraPosition.y + cameraGazeVector.y*imgPlane.distance;
   m.z = cameraPosition.z + cameraGazeVector.z*imgPlane.distance;
   Vector3f q;                      //0,0 noktası, m noktasını içeren u v duzleminde
   q.x = m.x + (cameraU.x*imgPlane.left) + (cameraV.x*imgPlane.top);
   q.y = m.y + (cameraU.y*imgPlane.left) + (cameraV.y*imgPlane.top);
   q.z = m.z + (cameraU.z*imgPlane.left) + (cameraV.z*imgPlane.top);


   Vector3f s;// kameradan s noktasına uzanan vektör s = (q + su*u- sv*v) - e(camera position)
   s.x = q.x + cameraU.x*su - cameraV.x*sv - cameraPosition.x;//unit vector al
   s.y = q.y + cameraU.y*su - cameraV.y*sv - cameraPosition.y;
   s.z = q.z + cameraU.z*su - cameraV.z*sv - cameraPosition.z;



   return Ray(cameraPosition,s);
}
