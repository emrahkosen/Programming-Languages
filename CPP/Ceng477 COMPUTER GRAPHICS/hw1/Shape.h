#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <vector>
#include "Ray.h"
#include "defs.h"
#include <climits>


using namespace std;





// Base class for any shape object
class Shape
{
public:
	int id;	        // Id of the shape
	int matIndex;	// Material index of the shape

	virtual ReturnVal intersect(const Ray & ray) const = 0; // Pure virtual method for intersection test. You must implement this for sphere, triangle, and mesh.

    Shape(void);
    Shape(int id, int matIndex); // Constructor

private:
	// Write any other stuff here
};







// Class for sphere
class Sphere: public Shape
{
public:
	Sphere(void);	// Constructor
	Sphere(int id, int matIndex, int cIndex, float R);	// Constructor
	ReturnVal intersect(const Ray & ray) const;	// Will take a ray and return a structure related to the intersection information. You will implement this.

private:
	// Write any other stuff here
	float R;//radious
	Vector3f Center;
	int cIndex;

	float dotProduct(Vector3f a, Vector3f b) const;
	float toNorm(const Vector3f a) const;//vektörün uzunlğu

};






// Class for triangle
class Triangle: public Shape
{
public:
	Triangle(void);	// Constructor
	Triangle(int id, int matIndex, int p1Index, int p2Index, int p3Index);	// Constructor
	ReturnVal intersect(const Ray & ray) const; // Will take a ray and return a structure related to the intersection information. You will implement this.

private:
	// Write any other stuff here
	int p1Index;
	int p2Index;
	int p3Index;
	Vector3f crosProduct(Vector3f a, Vector3f b) const;
	float toNorm(const Vector3f a) const;
	float dotProduct(Vector3f a, Vector3f b) const;
	float determinant(float a0,float a1, float a2,
										float b0,float b1, float b2,
										float c0,float c1, float c2) const;
};






// Class for mesh
class Mesh: public Shape
{
public:
	Mesh(void);	// Constructor
	Mesh(int id, int matIndex, const vector<Triangle>& faces);	// Constructor
	ReturnVal intersect(const Ray & ray) const; // Will take a ray and return a structure related to the intersection information. You will implement this.

private:
	// Write any other stuff here
	vector<Triangle> faces;
	float dotProduct(Vector3f a, Vector3f b) const;

};











#endif
