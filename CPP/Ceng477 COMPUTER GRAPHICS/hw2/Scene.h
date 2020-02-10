#ifndef _SCENE_H_
#define _SCENE_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Camera.h"
#include "Color.h"
#include "Model.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"

using namespace std;

class Scene
{
public:
	Color backgroundColor;
	bool cullingEnabled;
	int projectionType;

	vector< vector<Color> > image;
	vector< Camera* > cameras;
	vector< Vec3* > vertices;
	vector< Color* > colorsOfVertices;
	vector< Scaling* > scalings;
	vector< Rotation* > rotations;
	vector< Translation* > translations;
	vector< Model* > models;

	Scene(const char *xmlPath);

	void initializeImage(Camera* camera);
	void forwardRenderingPipeline(Camera* camera);
	int makeBetweenZeroAnd255(double value);
	void writeImageToPPMFile(Camera* camera);
	void convertPPMToPNG(string ppmFileName, int osType);



	/**********/
	Matrix4 rotateIt(Rotation & rotation);
	Matrix4 translateIt(Translation &translation);
	Matrix4 scaleIt(Scaling scaling);
	Matrix4 ModelTransform(Camera &camera , Model &model);
	Matrix4 CameraTransform(Camera &camera);
	Matrix4 Pers_Or_OrthProject(Camera &camera);
	Matrix4 ViewportTrans(Camera &camera);
	void draw(int x,int y, Color color,Camera &camera);
	void LineRasterization(Vec3 vertex0, Vec3 vertex1,Camera &camera);
	double min(double x, double y, double z);
	double max(double x, double y, double z);
	double powerf(double x,double y, Vec3 v1, Vec3 v2);

	/**********/
};

#endif
