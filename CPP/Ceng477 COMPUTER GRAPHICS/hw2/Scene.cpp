#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cmath>

#include "Scene.h"
#include "Camera.h"
#include "Color.h"
#include "Model.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "tinyxml2.h"
#include "Helpers.h"

using namespace tinyxml2;
using namespace std;

/*
	Transformations, clipping, culling, rasterization are done here.
	You can define helper functions inside Scene class implementation.
*/




/****************************/
/****************************/
Matrix4 Scene::rotateIt(Rotation &rotation)
{
	Vec3 u;
	Vec3 v;
	u.x = rotation.ux;
	u.y = rotation.uy;
	u.z = rotation.uz;
	u = normalizeVec3(u);
	double min = (u.x > u.y) ? ( ( u.y > u.z ) ? u.z : u.y ):( (u.x > u.z ) ? u.z: u.x);

	if(min == u.x)
	{
		v.x = 0.0;
		v.y = -1*u.z;
		v.z = u.y;
	}
	else if(min == u.y)
	{
		v.x = -1*u.z;
		v.y = 0.0;
		v.z = u.x;
	}
	else
	{
		v.x = -1*u.y;
		v.y = u.x;
		v.z = 0.0;
	}

	v =  normalizeVec3(v);
	Vec3 w = crossProductVec3(u,v);
	w =  normalizeVec3(w);

	Matrix4 M;
	Matrix4 Minverse;


	M.val[0][0] = u.x;
	M.val[0][1] = u.y;
	M.val[0][2] = u.z;
	//M.val[0][3] = 0;

	M.val[1][0] = v.x;
	M.val[1][1] = v.y;
	M.val[1][2] = v.z;
	//M.val[1][3] = 0;

	M.val[2][0] = w.x;
	M.val[2][1] = w.y;
	M.val[2][2] = w.z;
	//M.val[2][3] = 0;

	//M.val[3][0] = 0;
	//M.val[3][1] = 0;
	//M.val[3][2] = 0;
	M.val[3][3] = 1;


	Minverse.val[0][0] = u.x;
	Minverse.val[0][1] = v.x;
	Minverse.val[0][2] = w.x;
	//Minverse.val[0][3] = 0;
	Minverse.val[1][0] = u.y;
	Minverse.val[1][1] = v.y;
	Minverse.val[1][2] = w.y;
	//Minverse.val[1][3] = 0;

	Minverse.val[2][0] = u.z;
	Minverse.val[2][1] = v.z;
	Minverse.val[2][2] = w.z;
	//Minverse.val[1][3] = 0;

	//Minverse.val[3][0] = 0;
	//Minverse.val[3][1] = 0;
	//Minverse.val[3][2] = 0;
	Minverse.val[3][3] = 1.0;



	double angle = ( rotation.angle * M_PI / 180.0 );
	Matrix4 RotateX;

	RotateX.val[0][0] = 1.0;
	//RotateX.val[0][1] = 0;
	//RotateX.val[0][2] = 0;
	//RotateX.val[0][3] = 0;

	//RotateX.val[1][0] = 0;
	RotateX.val[1][1] = cos(angle);
	RotateX.val[1][2] = -1*sin(angle);
	//RotateX.val[1][3] = 0;

	//RotateX.val[2][0] = 0;
	RotateX.val[2][1] = sin(angle);
	RotateX.val[2][2] = cos(angle);
	//RotateX.val[2][3] = 0;

	//RotateX.val[3][0] = 0;
	//RotateX.val[3][1] = 0;
	//RotateX.val[3][2] = 0;
	RotateX.val[3][3] = 1.0;

	Matrix4 RoraredX = multiplyMatrixWithMatrix(RotateX,M);
	return multiplyMatrixWithMatrix(Minverse,RoraredX);


}
/**********************/
/**********************/
Matrix4 Scene::translateIt(Translation &translation)
{
	Matrix4 trans;

	trans.val[0][0] = 1.0;
	trans.val[0][1] = 0;
	trans.val[0][2] = 0;
	trans.val[0][3] = translation.tx;

	trans.val[1][0] = 0;
	trans.val[1][1] = 1.0;
	trans.val[1][2] = 0;
	trans.val[1][3] = translation.ty;

	trans.val[2][0] = 0;
	trans.val[2][1] = 0;
	trans.val[2][2] = 1.0;
	trans.val[2][3] = translation.tz;

	trans.val[3][0] = 0;
	trans.val[3][1] = 0;
	trans.val[3][2] = 0;
	trans.val[3][3] = 1.0;

	return trans;

}


/***********************/
/***********************/
Matrix4 Scene::scaleIt(Scaling scaling)
{
	Matrix4 scale;
	scale.val[0][0] =  scaling.sx;
	scale.val[1][1] =  scaling.sy;
	scale.val[2][2] =  scaling.sz;
	scale.val[3][3] =  1;
	/*remaining are all 0*/
	return scale;
}


/***************************/
/***************************/

Matrix4 Scene::ModelTransform(Camera &camera , Model &model)
{
	Matrix4 returnM = getIdentityMatrix();
	int numberOfTransformations = model.numberOfTransformations;
	for(int ithtrans = 0; ithtrans < numberOfTransformations; ithtrans++)
	{
		int transID = model.transformationIds[ithtrans];
		char transType = model.transformationTypes[ithtrans];/*can be r t s */
		if(transType == 'r')
		{
			Matrix4 rotationMatrix = rotateIt(*rotations[transID-1]);
			returnM = multiplyMatrixWithMatrix(rotationMatrix,returnM);
		}
		else if(transType == 't')
		{
			Matrix4 translateMatrix = translateIt(*translations[transID-1]);
			returnM = multiplyMatrixWithMatrix(translateMatrix,returnM);
		}
		else if(transType == 's')
		{
			Matrix4 scaleMatrix = scaleIt(*scalings[transID-1]);
			returnM = multiplyMatrixWithMatrix(scaleMatrix,returnM);
		}
		else
		{;/*ERROR*/}
	}
	return returnM;
}




Matrix4 Scene::CameraTransform(Camera &camera)
{
	Matrix4 Mcamera;
	Mcamera.val[0][0] = camera.u.x;
	Mcamera.val[0][1] = camera.u.y;
	Mcamera.val[0][2] = camera.u.z;
	Mcamera.val[0][3] = -1.0*(camera.u.x*camera.pos.x + camera.u.y*camera.pos.y + camera.u.z*camera.pos.z);

	Mcamera.val[1][0] = camera.v.x;
	Mcamera.val[1][1] = camera.v.y;
	Mcamera.val[1][2] = camera.v.z;
	Mcamera.val[1][3] = -1.0*(camera.v.x*camera.pos.x + camera.v.y*camera.pos.y + camera.v.z*camera.pos.z);

	Mcamera.val[2][0] = camera.w.x;
	Mcamera.val[2][1] = camera.w.y;
	Mcamera.val[2][2] = camera.w.z;
	Mcamera.val[2][3] = -1.0*(camera.w.x*camera.pos.x + camera.w.y*camera.pos.y + camera.w.z*camera.pos.z);

	Mcamera.val[3][0] = 0;
	Mcamera.val[3][1] = 0;
	Mcamera.val[3][2] = 0;
	Mcamera.val[3][3] = 1;

	return Mcamera;
}

Matrix4 Scene::Pers_Or_OrthProject(Camera &camera)
{

	if(projectionType )/*perspective*/
	{
		Matrix4 perspective;
		perspective.val[0][0] = (2.0*camera.near)/(camera.right - camera.left);
		//perspective.val[0][1] = 0.0;
		perspective.val[0][2] = (1.0*(camera.right + camera.left))/(camera.right - camera.left);
		//perspective.val[0][3] = 0.0;

		//perspective.val[1][0] = 0.0;
		perspective.val[1][1] = (2.0*camera.near) / (camera.top - camera.bottom);
		perspective.val[1][2] = (1.0*(camera.top + camera.bottom))/(camera.top - camera.bottom);
		//perspective.val[1][3] = 0.0;

		//perspective.val[2][0] = 0.0;
		//perspective.val[2][1] = 0.0;
		perspective.val[2][2] = (-1.0*(camera.far + camera.near)) / (camera.far - camera.near);
		perspective.val[2][3] = (-2.0*camera.far*camera.near) / (camera.far - camera.near);

		//perspective.val[3][0] = 0.0;
		//perspective.val[3][1] = 0.0;
		perspective.val[3][2] = -1.0;
		//perspective.val[3][3] = 0.0;

		return perspective;
	}
	else /*orthographic*/
	{
		Matrix4 orthographic;
		orthographic.val[0][0] = (2.0)/(camera.right - camera.left);
		orthographic.val[0][1] = 0;
		orthographic.val[0][2] = 0;
		orthographic.val[0][3] = (-1.0*(camera.right + camera.left))/(camera.right - camera.left);

		orthographic.val[1][0] = 0;
		orthographic.val[1][1] = (2.0)/(camera.top - camera.bottom);
		orthographic.val[1][2] = 0;
		orthographic.val[1][3] = (-1.0*(camera.top + camera.bottom))/(camera.top - camera.bottom);

		orthographic.val[2][0] = 0;
		orthographic.val[2][1] = 0;
		orthographic.val[2][2] = (-2.0)/ (camera.far - camera.near);
		orthographic.val[2][3] = (-1.0*(camera.far + camera.near)) / (camera.far - camera.near);

		orthographic.val[3][0] = 0;
		orthographic.val[3][1] = 0;
		orthographic.val[3][2] = 0;
		orthographic.val[3][3] = 1;
		return orthographic;
	}
}



Matrix4 Scene::ViewportTrans(Camera &camera)
{
	Matrix4 viewP;
	viewP.val[0][0] = camera.horRes/2.0;/*integer float  belli değil*/
	viewP.val[0][3] = (camera.horRes - 1)*0.5;
	viewP.val[1][1] = camera.verRes/2.0;
	viewP.val[1][3] = (camera.verRes - 1)*0.5;
	viewP.val[2][2] = 0.5;
	viewP.val[2][3] = 0.5;
	return viewP;
}
void Scene::draw(int x,int y, Color color, Camera &camera )
{

	if(x >= 0 && y >= 0 && x < camera.horRes && y < camera.verRes)
	{

		if(color.r > 255)
			image[x][y].r = 255;
		else if(color.r < 0)
			image[x][y].r = 0;
		else
			image[x][y].r = (int)color.r;

		if(color.g > 255)
			image[x][y].g = 255;
		else if(color.g < 0)
			image[x][y].g = 0;
		else
			image[x][y].g = (int)color.g;

		if(color.b > 255)
			image[x][y].b = 255;
		else if(color.b < 0)
			image[x][y].b = 0;
		else
			image[x][y].b = (int)color.b;

	}
}
void Scene::LineRasterization(Vec3 vertex0, Vec3 vertex1, Camera &camera)
{
	Color c0;
	c0.r = colorsOfVertices[vertex0.colorId-1]->r;
	c0.g = colorsOfVertices[vertex0.colorId-1]->g;
	c0.b = colorsOfVertices[vertex0.colorId-1]->b;
	Color c1 = *colorsOfVertices[vertex1.colorId-1];

	if(vertex1.x - vertex0.x > 0)
	{
		double m = (double)(vertex1.y-vertex0.y)/(double)(vertex1.x-vertex0.x);
		if(m >= 0 && m <= 1)
		{
			int y = vertex0.y;
			double d = vertex0.y - vertex1.y + 0.5*(vertex1.x - vertex0.x);
			Color c = c0;
			Color dc;
			dc.r = (c1.r-c0.r)/(double)(vertex1.x-vertex0.x);
			dc.g = (c1.g-c0.g)/(double)(vertex1.x-vertex0.x);
			dc.b = (c1.b-c0.b)/(double)(vertex1.x-vertex0.x);
			for(int x = vertex0.x; x < vertex1.x; x++)
			{
				draw(x,y,c,camera);
				if(d < 0)
				{
					y++;
					d += vertex0.y- vertex1.y + vertex1.x -vertex0.x;
				}
				else
				{
					d += vertex0.y- vertex1.y;
				}

				c.r = c.r + dc.r;
				c.g = c.g + dc.g;
				c.b = c.b + dc.b;
			}

		}
		else if(m > 1)
		{
				int x = vertex0.x;
				double d = vertex0.x - vertex1.x + 0.5*(vertex1.y - vertex0.y);
				Color c = c0;
				Color dc;
				dc.r = (c1.r-c0.r)/(double)(vertex1.y-vertex0.y);
				dc.g = (c1.g-c0.g)/(double)(vertex1.y-vertex0.y);
				dc.b = (c1.b-c0.b)/(double)(vertex1.y-vertex0.y);
				for(int y = vertex0.y; y < vertex1.y ; y++ )
				{
					draw(x,y,c,camera);
					if(d < 0)
					{
						x++;
						d += vertex0.x - vertex1.x + (vertex1.y - vertex0.y);
					}
					else
					{
						d += vertex0.x - vertex1.x;
					}
					c.r = c.r + dc.r;
					c.g = c.g + dc.g;
					c.b = c.b + dc.b;
				}
		}
		else
			LineRasterization(vertex1,vertex0 , camera);/*for region 3*/
	}
	else if(vertex1.x - vertex0.x < 0)
	{
		double m = (double)(vertex1.y-vertex0.y)/(double)(vertex1.x-vertex0.x);
		if(m < -1)
		{
			int x = vertex0.x;
			double d = (vertex1.x-vertex0.x)+0.5*(vertex1.y-vertex0.y);
			Color c = c0;
			Color dc;
			dc.r=(c1.r-c0.r)/(double)(vertex1.y-vertex0.y);
			dc.g=(c1.g-c0.g)/(double)(vertex1.y-vertex0.y);
			dc.b=(c1.b-c0.b)/(double)(vertex1.y-vertex0.y);
			for(int y = vertex0.y; y < vertex1.y; y++ )
			{
				draw(x,y,c, camera);
				if(d < 0)
				{
					x= x - 1;
					d += (vertex1.x-vertex0.x) + (vertex1.y-vertex0.y);
				}
				else
				{
					d += (vertex1.x-vertex0.x);
				}
				c.r = c.r + dc.r;
				c.g = c.g + dc.g;
				c.b = c.b + dc.b;
			}
		}

		else if(m >= -1 && m <= 0 )
		{
			int y = vertex0.y;
			double d = (vertex0.y-vertex1.y)+ 0.5*(vertex0.x-vertex1.x);
			Color c = c0;
			Color dc;
			dc.r = (c1.r - c0.r)/(double)(vertex0.x-vertex1.x);
			dc.g = (c1.g - c0.g)/(double)(vertex0.x-vertex1.x);
			dc.b = (c1.b - c0.b)/(double)(vertex0.x-vertex1.x);

			for(int x = vertex0.x; x > vertex1.x; x-- )
			{
				draw(x,y,c,camera);
				if(d < 0)
				{
					y = y+1;
					d += (vertex0.y-vertex1.y) + (vertex0.x-vertex1.x);
				}
				else
				{
					d += (vertex0.y-vertex1.y);
				}
				c.r = c.r + dc.r;
				c.g = c.g + dc.g;
				c.b = c.b + dc.b;
			}
		}
		else
		 LineRasterization(vertex1,vertex0,camera);
	}
}

double Scene::min(double x, double y, double z)
{
	return (x > y) ? ( ( y > z ) ? z : y ):( (x > z ) ? z: x);
}

double Scene::max(double x, double y, double z)
{
	return (x < y) ? ( ( y < z ) ? z : y ):( (x < z ) ? z: x);
}
double Scene::powerf(double x,double y, Vec3 v1, Vec3 v2)
{
	return x*(v1.y-v2.y)+y*(v2.x-v1.x)+v1.x*v2.y-v1.y*v2.x;
}


/*****************************************************/
void Scene::forwardRenderingPipeline(Camera *camera)
{

	Matrix4 Mcamera = CameraTransform(*camera);
	Matrix4 persOrt = Pers_Or_OrthProject(*camera);//If projectionType is 0, that means you need to apply orthographic projection, If it is 1, you should apply perspective projection.
	Matrix4 viewPort3d = ViewportTrans(*camera);/* bidaha bak*/

	for(auto &model : models)
	{
		Matrix4 Mmodel = ModelTransform(*camera, *model);

		Matrix4 camera_X_model = multiplyMatrixWithMatrix(Mcamera,Mmodel);
		Matrix4 perspec_X_camera_X_model = multiplyMatrixWithMatrix(persOrt,camera_X_model);





		int isProcessed[vertices.size() + 1 ];
		for(int i = 0; i< vertices.size() + 1; i++)
			isProcessed[i] = 0;




		Vec4 cullingVertices[vertices.size()+1 ];

		for(int i = 0; i< vertices.size(); i++)
		{
			cullingVertices[i+1].x = vertices[i]->x;
			cullingVertices[i+1].y = vertices[i]->y;
			cullingVertices[i+1].z = vertices[i]->z;
			cullingVertices[i+1].t = 1;
			cullingVertices[i+1].colorId = vertices[i]->colorId;
		}

/***************/

		for(auto &triangle : model->triangles)
		{
			for(int i = 0; i < 3; i++)
			{
				int vertexIndex = triangle.vertexIds[i];
				if(isProcessed[vertexIndex] == 0)/*if not proceed*/
				{
					Vec4 currentVertex;
					currentVertex.x = vertices[vertexIndex-1]->x;
					currentVertex.y = vertices[vertexIndex-1]->y;
					currentVertex.z = vertices[vertexIndex-1]->z;
					currentVertex.t = 1;

					Vec4 vMultiplied = multiplyMatrixWithVec4(perspec_X_camera_X_model, currentVertex);

					cullingVertices[vertexIndex].x = vMultiplied.x/vMultiplied.t;
					cullingVertices[vertexIndex].y = vMultiplied.y/vMultiplied.t;
					cullingVertices[vertexIndex].z = vMultiplied.z/vMultiplied.t;
					cullingVertices[vertexIndex].t = vMultiplied.t/vMultiplied.t;
					//cullingVertices[vertexIndex].colorId = vertices[vertexIndex-1]->colorId;
					isProcessed[vertexIndex] = 1;
				}
			}
		}


			int rasterizeIT[model->numberOfTriangles ];
			for(int i = 0; i < model->numberOfTriangles; i++)
				rasterizeIT[i] = 1;





			if(cullingEnabled)//backface culling
			{
				for (size_t i = 0; i < model->numberOfTriangles; i++)
				{
						Vec3 A;
						Vec3 B;
						Vec3 C;
						A.x = cullingVertices[model->triangles[i].vertexIds[0]].x;
						A.y = cullingVertices[model->triangles[i].vertexIds[0]].y;
						A.z = cullingVertices[model->triangles[i].vertexIds[0]].z;

						B.x = cullingVertices[model->triangles[i].vertexIds[1]].x;
						B.y = cullingVertices[model->triangles[i].vertexIds[1]].y;
						B.z = cullingVertices[model->triangles[i].vertexIds[1]].z;

						C.x = cullingVertices[model->triangles[i].vertexIds[2]].x;
						C.y = cullingVertices[model->triangles[i].vertexIds[2]].y;
						C.z = cullingVertices[model->triangles[i].vertexIds[2]].z;

						Vec3 centerOfTriangle;
						centerOfTriangle.x = (A.x+ B.x + C.x)/3.0;
						centerOfTriangle.y = (A.y+ B.y + C.y)/3.0;
						centerOfTriangle.z = (A.z+ B.z + C.z)/3.0;




						Vec3 v = normalizeVec3(centerOfTriangle);
						Vec3 AB = subtractVec3(B,A);
						AB = normalizeVec3(AB);
						Vec3 AC = subtractVec3(C,A);
						AC = normalizeVec3(AC);
						Vec3 n = normalizeVec3(crossProductVec3(AB, AC));

						double dotpro = dotProductVec3(v,n);

						if(dotpro < 0)
								rasterizeIT[i] = 0;
				}
			}


			Vec3 pixelCoordinates[ vertices.size() + 1];
			pixelCoordinates[0].x = 0;
			pixelCoordinates[0].y = 0;
			pixelCoordinates[0].z = 0;
			pixelCoordinates[0].colorId = 1;

			for(int i = 1; i< vertices.size()+1;i++)
			{
				pixelCoordinates[i].x = cullingVertices[i].x;
				pixelCoordinates[i].y = cullingVertices[i].y;
				pixelCoordinates[i].z = cullingVertices[i].z;
				pixelCoordinates[i].colorId = cullingVertices[i].colorId;
			}






			for(auto &triangle : model->triangles)
			{

				for(int i = 0; i< 3; i++)
				{
					int vertex = triangle.vertexIds[i];
					Vec4 res = multiplyMatrixWithVec4(viewPort3d,cullingVertices[vertex] );
					pixelCoordinates[ vertex ].x = res.x;
					pixelCoordinates[ vertex ].y = res.y;
				}
			}



			if(model->type == 0)/*0 for wireframe,*/
			{
				for(int i = 0; i< model->triangles.size(); i++)
				{
					if(rasterizeIT[i] == 1)
					{
						int ver0 = model->triangles[i].vertexIds[0];
						int ver1 = model->triangles[i].vertexIds[1];
						int ver2 = model->triangles[i].vertexIds[2];
						LineRasterization(pixelCoordinates[ver0], pixelCoordinates[ver1],*camera);
						LineRasterization(pixelCoordinates[ver1], pixelCoordinates[ver2],*camera);
						LineRasterization(pixelCoordinates[ver2], pixelCoordinates[ver0],*camera);
					}
				}

			}

			else  /*1 for solid*/
			{
				for(int i = 0; i< model->triangles.size(); i++)
				{

					if(rasterizeIT[i] == 1)
					{

						Vec3 v0 = pixelCoordinates[model->triangles[i].vertexIds[0]];
						Vec3 v1 = pixelCoordinates[model->triangles[i].vertexIds[1]];
						Vec3 v2 = pixelCoordinates[model->triangles[i].vertexIds[2]];

						Color c0 = *colorsOfVertices[v0.colorId-1];
						Color c1 = *colorsOfVertices[v1.colorId-1];
						Color c2 = *colorsOfVertices[v2.colorId-1];

						int ymin = min(v0.y, v1.y, v2.y);
						int xmax = max(v0.x, v1.x, v2.x);
						int ymax = max(v0.y, v1.y, v2.y);
						for(;ymin<= ymax; ymin++ )
						{
							int xmin = min(v0.x, v1.x, v2.x);
							for(; xmin<= xmax; xmin++)
							{
								double alfa = powerf(xmin,ymin,v1,v2)/powerf(v0.x,v0.y,v1,v2);
								double beta = powerf(xmin,ymin,v2,v0)/powerf(v1.x,v1.y,v2,v0);
								double gama = powerf(xmin,ymin,v0,v1)/powerf(v2.x,v2.y,v0,v1);

								if( alfa >= 0 && beta >= 0 && gama >= 0)
								{
									Color c;
									c.r = alfa*c0.r + beta*c1.r + gama*c2.r;
									c.g = alfa*c0.g + beta*c1.g + gama*c2.g;
									c.b = alfa*c0.b + beta*c1.b + gama*c2.b;
									draw(xmin,ymin,c,*camera);
								}

							}
						}

					}
				}
			}



	}
}

/*
	Parses XML file
*/
Scene::Scene(const char *xmlPath)
{
	const char *str;
	XMLDocument xmlDoc;
	XMLElement *pElement;

	xmlDoc.LoadFile(xmlPath);

	XMLNode *pRoot = xmlDoc.FirstChild();

	// read background color
	pElement = pRoot->FirstChildElement("BackgroundColor");
	str = pElement->GetText();
	sscanf(str, "%lf %lf %lf", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);

	// read culling
	pElement = pRoot->FirstChildElement("Culling");
	if (pElement != NULL)
		pElement->QueryBoolText(&cullingEnabled);

	// read projection type
	pElement = pRoot->FirstChildElement("ProjectionType");
	if (pElement != NULL)
		pElement->QueryIntText(&projectionType);

	// read cameras
	pElement = pRoot->FirstChildElement("Cameras");
	XMLElement *pCamera = pElement->FirstChildElement("Camera");
	XMLElement *camElement;
	while (pCamera != NULL)
	{
		Camera *cam = new Camera();

		pCamera->QueryIntAttribute("id", &cam->cameraId);

		camElement = pCamera->FirstChildElement("Position");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->pos.x, &cam->pos.y, &cam->pos.z);

		camElement = pCamera->FirstChildElement("Gaze");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->gaze.x, &cam->gaze.y, &cam->gaze.z);

		camElement = pCamera->FirstChildElement("Up");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->v.x, &cam->v.y, &cam->v.z);

		cam->gaze = normalizeVec3(cam->gaze);
		cam->u = crossProductVec3(cam->gaze, cam->v);
		cam->u = normalizeVec3(cam->u);

		cam->w = inverseVec3(cam->gaze);
		cam->v = crossProductVec3(cam->u, cam->gaze);
		cam->v = normalizeVec3(cam->v);

		camElement = pCamera->FirstChildElement("ImagePlane");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf %lf %lf %lf %d %d",
			   &cam->left, &cam->right, &cam->bottom, &cam->top,
			   &cam->near, &cam->far, &cam->horRes, &cam->verRes);

		camElement = pCamera->FirstChildElement("OutputName");
		str = camElement->GetText();
		cam->outputFileName = string(str);

		cameras.push_back(cam);

		pCamera = pCamera->NextSiblingElement("Camera");
	}

	// read vertices
	pElement = pRoot->FirstChildElement("Vertices");
	XMLElement *pVertex = pElement->FirstChildElement("Vertex");
	int vertexId = 1;

	while (pVertex != NULL)
	{
		Vec3 *vertex = new Vec3();
		Color *color = new Color();

		vertex->colorId = vertexId;

		str = pVertex->Attribute("position");
		sscanf(str, "%lf %lf %lf", &vertex->x, &vertex->y, &vertex->z);

		str = pVertex->Attribute("color");
		sscanf(str, "%lf %lf %lf", &color->r, &color->g, &color->b);

		vertices.push_back(vertex);
		colorsOfVertices.push_back(color);

		pVertex = pVertex->NextSiblingElement("Vertex");

		vertexId++;
	}

	// read translations
	pElement = pRoot->FirstChildElement("Translations");
	XMLElement *pTranslation = pElement->FirstChildElement("Translation");
	while (pTranslation != NULL)
	{
		Translation *translation = new Translation();

		pTranslation->QueryIntAttribute("id", &translation->translationId);

		str = pTranslation->Attribute("value");
		sscanf(str, "%lf %lf %lf", &translation->tx, &translation->ty, &translation->tz);

		translations.push_back(translation);

		pTranslation = pTranslation->NextSiblingElement("Translation");
	}

	// read scalings
	pElement = pRoot->FirstChildElement("Scalings");
	XMLElement *pScaling = pElement->FirstChildElement("Scaling");
	while (pScaling != NULL)
	{
		Scaling *scaling = new Scaling();

		pScaling->QueryIntAttribute("id", &scaling->scalingId);
		str = pScaling->Attribute("value");
		sscanf(str, "%lf %lf %lf", &scaling->sx, &scaling->sy, &scaling->sz);

		scalings.push_back(scaling);

		pScaling = pScaling->NextSiblingElement("Scaling");
	}

	// read rotations
	pElement = pRoot->FirstChildElement("Rotations");
	XMLElement *pRotation = pElement->FirstChildElement("Rotation");
	while (pRotation != NULL)
	{
		Rotation *rotation = new Rotation();

		pRotation->QueryIntAttribute("id", &rotation->rotationId);
		str = pRotation->Attribute("value");
		sscanf(str, "%lf %lf %lf %lf", &rotation->angle, &rotation->ux, &rotation->uy, &rotation->uz);

		rotations.push_back(rotation);

		pRotation = pRotation->NextSiblingElement("Rotation");
	}

	// read models
	pElement = pRoot->FirstChildElement("Models");

	XMLElement *pModel = pElement->FirstChildElement("Model");
	XMLElement *modelElement;
	while (pModel != NULL)
	{
		Model *model = new Model();

		pModel->QueryIntAttribute("id", &model->modelId);
		pModel->QueryIntAttribute("type", &model->type);

		// read model transformations
		XMLElement *pTransformations = pModel->FirstChildElement("Transformations");
		XMLElement *pTransformation = pTransformations->FirstChildElement("Transformation");

		pTransformations->QueryIntAttribute("count", &model->numberOfTransformations);

		while (pTransformation != NULL)
		{
			char transformationType;
			int transformationId;

			str = pTransformation->GetText();
			sscanf(str, "%c %d", &transformationType, &transformationId);

			model->transformationTypes.push_back(transformationType);
			model->transformationIds.push_back(transformationId);

			pTransformation = pTransformation->NextSiblingElement("Transformation");
		}

		// read model triangles
		XMLElement *pTriangles = pModel->FirstChildElement("Triangles");
		XMLElement *pTriangle = pTriangles->FirstChildElement("Triangle");

		pTriangles->QueryIntAttribute("count", &model->numberOfTriangles);

		while (pTriangle != NULL)
		{
			int v1, v2, v3;

			str = pTriangle->GetText();
			sscanf(str, "%d %d %d", &v1, &v2, &v3);

			model->triangles.push_back(Triangle(v1, v2, v3));

			pTriangle = pTriangle->NextSiblingElement("Triangle");
		}

		models.push_back(model);

		pModel = pModel->NextSiblingElement("Model");
	}
}

/*
	Initializes image with background color
*/
void Scene::initializeImage(Camera *camera)
{
	if (this->image.empty())
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			vector<Color> rowOfColors;

			for (int j = 0; j < camera->verRes; j++)
			{
				rowOfColors.push_back(this->backgroundColor);
			}

			this->image.push_back(rowOfColors);
		}
	}
	// if image is filled before, just change color rgb values with the background color
	else
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			for (int j = 0; j < camera->verRes; j++)
			{
				this->image[i][j].r = this->backgroundColor.r;
				this->image[i][j].g = this->backgroundColor.g;
				this->image[i][j].b = this->backgroundColor.b;
			}
		}
	}
}

/*
	If given value is less than 0, converts value to 0.
	If given value is more than 255, converts value to 255.
	Otherwise returns value itself.
*/
int Scene::makeBetweenZeroAnd255(double value)
{
	if (value >= 255.0)
		return 255;
	if (value <= 0.0)
		return 0;
	return (int)(value);
}

/*
	Writes contents of image (Color**) into a PPM file.
*/
void Scene::writeImageToPPMFile(Camera *camera)
{
	ofstream fout;

	fout.open(camera->outputFileName.c_str());

	fout << "P3" << endl;
	fout << "# " << camera->outputFileName << endl;
	fout << camera->horRes << " " << camera->verRes << endl;
	fout << "255" << endl;

	for (int j = camera->verRes - 1; j >= 0; j--)
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			fout << makeBetweenZeroAnd255(this->image[i][j].r) << " "
				 << makeBetweenZeroAnd255(this->image[i][j].g) << " "
				 << makeBetweenZeroAnd255(this->image[i][j].b) << " ";
		}
		fout << endl;
	}
	fout.close();
}

/*
	Converts PPM image in given path to PNG file, by calling ImageMagick's 'convert' command.
	os_type == 1 		-> Ubuntu
	os_type == 2 		-> Windows
	os_type == other	-> No conversion
*/
void Scene::convertPPMToPNG(string ppmFileName, int osType)
{
	string command;

	// call command on Ubuntu
	if (osType == 1)
	{
		command = "convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// call command on Windows
	else if (osType == 2)
	{
		command = "magick convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// default action - don't do conversion
	else
	{
	}
}
