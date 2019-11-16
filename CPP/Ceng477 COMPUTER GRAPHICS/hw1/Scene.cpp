#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Shape.h"
#include "tinyxml2.h"
#include "Image.h"
#include <iostream>

using namespace tinyxml2;

/*
 * Must render the scene from each camera's viewpoint and create an image.
 * You can use the methods of the Image class to save the image as a PPM file.
 */
float Scene::getDistance(Vector3f a, Vector3f b)
{
	return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z) );
}




ReturnVal Scene::getPoint(Ray ray)
{
		vector<ReturnVal> points;

		int lenObjects = objects.size();
		for(int i = 0; i <  lenObjects; i++) //bu for döngüsünde bütün objeleri kontrol edip
		{                                       //kesişen noktaları buluyor
			ReturnVal tmpPoint = objects[i]->intersect(ray);


			if(tmpPoint.isInShape == true)
			{

					points.push_back(tmpPoint);
			}
		}





		if(points.size() == 0)//eger vektor boşsa false deger donene bir ReturnVal döner
		{
			ReturnVal point;
			point.isInShape = false;
			return point;
		}
		else// ray bir objeyle kesişiyorsa en yakındaki objenin ReturnVal değerini döner
		{
			int pointNo = 0;
			float dist = getDistance(ray.origin, points[0].intersectPoint);

			for(int i = 1; i < points.size(); i++)
			{
				float tmpDist = getDistance(ray.origin, points[i].intersectPoint);
				if(dist > tmpDist)
				{
					dist = tmpDist;
					pointNo = i;
				}
			}
			return points[pointNo];
		}

}







Vector3f Scene::GetUnitVectorWith2Point(Vector3f a,Vector3f b)
{
	float distance = getDistance(a, b);
	Vector3f ret;
	ret.x = (a.x - b.x)/distance;
	ret.y = (a.y - b.y)/distance;
	ret.z = (a.z - b.z)/distance;

	return ret;
}

float Scene::dotproduct(Vector3f a, Vector3f b)
{
	    return a.x*b.x + a.y*b.y + a.z*b.z;
}





Vector3f Scene::FindDiffuseAndSpecular(PointLight &light, ReturnVal &point, Vector3f &pTol ,Ray & ray)
{

	Vector3f ret;
	Vector3f contri = light.computeLightContribution(point.intersectPoint);

	float dotProduct = fmax(dotproduct(pTol,point.Normal)/(sqrt(dotproduct(pTol,pTol)) * sqrt(dotproduct(point.Normal,point.Normal))),0);//dotproduct(pTol,point.Normal);

	dotProduct = (dotProduct<=0.0)?0:dotProduct;
	/*diffuse part*/
	ret.x = materials[point.materialID-1]->diffuseRef.x*dotProduct*contri.x;
	ret.y = materials[point.materialID-1]->diffuseRef.y*dotProduct*contri.y;
	ret.z = materials[point.materialID-1]->diffuseRef.z*dotProduct*contri.z;









	Vector3f halfV;// point den ışık kaynagına giden raydan kameradan pointe gelen rayi çıkartıyoruz
	halfV.x = pTol.x - ray.direction.x;
	halfV.y = pTol.y - ray.direction.y;
	halfV.z = pTol.z - ray.direction.z;
	float len =  sqrtf(halfV.x*halfV.x + halfV.y*halfV.y + halfV.z*halfV.z);
	halfV.x /= len;//ve normalini alıyoruz
	halfV.y /= len;
	halfV.z /= len;

	float cosalfa = fmax(dotproduct(halfV,point.Normal)/(sqrt(dotproduct(halfV,halfV)) * sqrt(dotproduct(point.Normal,point.Normal))),0); // dotproduct(point.Normal, halfV);
	cosalfa = (cosalfa<=0)?0:cosalfa;   //max(0,halfvector)


	ret.x += materials[point.materialID-1]->specularRef.x * pow(cosalfa,materials[point.materialID-1]->phongExp)*contri.x;
	ret.y += materials[point.materialID-1]->specularRef.y * pow(cosalfa,materials[point.materialID-1]->phongExp)*contri.y;
	ret.z += materials[point.materialID-1]->specularRef.z * pow(cosalfa,materials[point.materialID-1]->phongExp)*contri.z;


	return ret;
}








Vector3f Scene::colorize(ReturnVal &point, int maxDepth, Ray &ray )
{
	int lightNo = lights.size();
	int lenObjects = objects.size();
	Vector3f retColor;


	int materialID = point.materialID;
	float p1 = materials[materialID - 1]->ambientRef.x * ambientLight.x;
	float p2 = materials[materialID - 1]->ambientRef.y * ambientLight.y;
	float p3 = materials[materialID - 1]->ambientRef.z * ambientLight.z;
	for(size_t i = 0; i < lightNo; i++)
	{
		bool inShadow = false;
		PointLight &light = *lights[i];
		Vector3f pTol = GetUnitVectorWith2Point(light.position,point.intersectPoint); //point ile light arası vektör; point to light


		Vector3f pTolEpsilon;//noktanın ışık kaynaga biraz daha yakın olarak tanımladık
												// Shading bakarken karısşıklık olmasın
		pTolEpsilon.x = pTol.x * shadowRayEps +  point.intersectPoint.x;
		pTolEpsilon.y = pTol.y * shadowRayEps +  point.intersectPoint.y;
		pTolEpsilon.z = pTol.z * shadowRayEps +  point.intersectPoint.z;






		Ray ShadowRay(pTolEpsilon,pTol);// bizim pointimizin ışık noktasına giden ray bu ray pointin epsilon kadar ilerlettik

		ReturnVal shadowPoint;

    float tlight = ShadowRay.gett(light.position);


		for(int i = 0; i < lenObjects; i++ )// bütün obj bakılır herhangi bir gölge varsa durur.inShadow = true olur
		{
			shadowPoint = objects[i]->intersect(ShadowRay);

			if(shadowPoint.isInShape == true )
			{

				float ti = ShadowRay.gett(shadowPoint.intersectPoint);

				if( ti < tlight && ti >= 0  )
				{
					inShadow = true;
					break;
				}
			}
		}


		if(!inShadow )
		{
			Vector3f dspec = FindDiffuseAndSpecular(light,point,pTol,ray);
			p1 += dspec.x;
			p2 += dspec.y;
			p3 += dspec.z;

		}
	}



	/*      mirror       */
	if(maxDepth > 0 && (materials[materialID-1]->mirrorRef.x > 0
									 || materials[materialID-1]->mirrorRef.y > 0
									 || materials[materialID-1]->mirrorRef.z > 0))
	{
		float dotP = -2*dotproduct(ray.direction,point.Normal);
		Vector3f normDot;

		normDot.x = point.Normal.x*dotP + ray.direction.x;
		normDot.y = point.Normal.y*dotP + ray.direction.y;
		normDot.z = point.Normal.z*dotP + ray.direction.z;

		float norm = sqrt(normDot.x*normDot.x + normDot.y*normDot.y + normDot.z*normDot.z);
		normDot.x /= norm;
		normDot.y /= norm;
		normDot.z /= norm;



		Vector3f normDotEpsilon;//noktanın ışık kaynaga biraz daha yakın olarak tanımladık
												// Shading bakarken karısşıklık olmasın
		normDotEpsilon.x = normDot.x * shadowRayEps +  point.intersectPoint.x;
		normDotEpsilon.y = normDot.y * shadowRayEps +  point.intersectPoint.y;
		normDotEpsilon.z = normDot.z * shadowRayEps +  point.intersectPoint.z;


		Ray mirrorReflection(normDotEpsilon,normDot);
		ReturnVal mirrorPoint =  getPoint(mirrorReflection);


    if(mirrorPoint.isInShape && !(mirrorPoint.id == point.id && mirrorPoint.type == point.type))
		{
				Vector3f reflect =  colorize(mirrorPoint, maxDepth - 1,mirrorReflection);
				p1 +=  reflect.x*materials[materialID-1]->mirrorRef.x;
				p2 +=  reflect.y*materials[materialID-1]->mirrorRef.y;
				p3 +=  reflect.z*materials[materialID-1]->mirrorRef.z;
		}

	}


	retColor.x = p1;
	retColor.y = p2;
	retColor.z = p3;
	return retColor;

}





void Scene::renderScene(void)
{


	 for (int i = 0; i <  cameras.size(); i++)
	 {
		 Camera &camera = *cameras[i];
		int cHeight = camera.imgPlane.ny;
		int cWidth = camera.imgPlane.nx;

		Image image(cWidth,cHeight); // imageler olustu h*w boyutta
		for(int height = 0 ; height < cHeight;height++)
		{
			for(size_t width = 0; width < cWidth;width++)
			{

				Ray ray = camera.getPrimaryRay(width,height);


				ReturnVal point = getPoint(ray); // gecen rayın ilk kesiştiği noktayı buluyor


				Vector3f colorOfPoint = backgroundColor;
				if(point.isInShape == true)
				{
				 colorOfPoint = colorize(point, maxRecursionDepth,ray);
				}
				Color color;

				if(colorOfPoint.x > 255)
				 color.channel[0] = 255;
				else
				 	color.channel[0] = round(colorOfPoint.x);

				if(colorOfPoint.y > 255)
					 color.channel[1] = 255;
				else
					 color.channel[1] = round(colorOfPoint.y);
				if(colorOfPoint.z > 255)
					 color.channel[2] = 255;
				else
					 color.channel[2] = round(colorOfPoint.z);


				image.setPixelValue(width,height,color);



			}
		}
		image.saveImage(camera.imageName);
	 }
}














// Parses XML file.
Scene::Scene(const char *xmlPath)
{
	const char *str;
	XMLDocument xmlDoc;
	XMLError eResult;
	XMLElement *pElement;

	maxRecursionDepth = 1;
	shadowRayEps = 0.001;
	eResult = xmlDoc.LoadFile(xmlPath);

	XMLNode *pRoot = xmlDoc.FirstChild();

	pElement = pRoot->FirstChildElement("MaxRecursionDepth");
	if(pElement != nullptr)
		pElement->QueryIntText(&maxRecursionDepth);

	pElement = pRoot->FirstChildElement("BackgroundColor");
	str = pElement->GetText();
	sscanf(str, "%f %f %f", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);

	pElement = pRoot->FirstChildElement("ShadowRayEpsilon");
	if(pElement != nullptr)
		pElement->QueryFloatText(&shadowRayEps);

	pElement = pRoot->FirstChildElement("IntersectionTestEpsilon");
	if(pElement != nullptr)
		eResult = pElement->QueryFloatText(&intTestEps);

	// Parse cameras
	pElement = pRoot->FirstChildElement("Cameras");
	XMLElement *pCamera = pElement->FirstChildElement("Camera");
	XMLElement *camElement;
	while(pCamera != nullptr)
	{
        int id;
        char imageName[64];
        Vector3f pos, gaze, up;
        ImagePlane imgPlane;

		eResult = pCamera->QueryIntAttribute("id", &id);
		camElement = pCamera->FirstChildElement("Position");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &pos.x, &pos.y, &pos.z);
		camElement = pCamera->FirstChildElement("Gaze");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &gaze.x, &gaze.y, &gaze.z);
		camElement = pCamera->FirstChildElement("Up");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &up.x, &up.y, &up.z);
		camElement = pCamera->FirstChildElement("NearPlane");
		str = camElement->GetText();
		sscanf(str, "%f %f %f %f", &imgPlane.left, &imgPlane.right, &imgPlane.bottom, &imgPlane.top);
		camElement = pCamera->FirstChildElement("NearDistance");
		eResult = camElement->QueryFloatText(&imgPlane.distance);
		camElement = pCamera->FirstChildElement("ImageResolution");
		str = camElement->GetText();
		sscanf(str, "%d %d", &imgPlane.nx, &imgPlane.ny);
		camElement = pCamera->FirstChildElement("ImageName");
		str = camElement->GetText();
		strcpy(imageName, str);

		cameras.push_back(new Camera(id, imageName, pos, gaze, up, imgPlane));

		pCamera = pCamera->NextSiblingElement("Camera");

	}


	// Parse materals
	pElement = pRoot->FirstChildElement("Materials");
	XMLElement *pMaterial = pElement->FirstChildElement("Material");
	XMLElement *materialElement;
	while(pMaterial != nullptr)
	{
		materials.push_back(new Material());
		int curr = materials.size() - 1;

		eResult = pMaterial->QueryIntAttribute("id", &materials[curr]->id);
		materialElement = pMaterial->FirstChildElement("AmbientReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->ambientRef.r, &materials[curr]->ambientRef.g, &materials[curr]->ambientRef.b);
		materialElement = pMaterial->FirstChildElement("DiffuseReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->diffuseRef.r, &materials[curr]->diffuseRef.g, &materials[curr]->diffuseRef.b);
		materialElement = pMaterial->FirstChildElement("SpecularReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->specularRef.r, &materials[curr]->specularRef.g, &materials[curr]->specularRef.b);
		materialElement = pMaterial->FirstChildElement("MirrorReflectance");
		if(materialElement != nullptr)
		{
			str = materialElement->GetText();
			sscanf(str, "%f %f %f", &materials[curr]->mirrorRef.r, &materials[curr]->mirrorRef.g, &materials[curr]->mirrorRef.b);
		}
				else
		{
			materials[curr]->mirrorRef.r = 0.0;
			materials[curr]->mirrorRef.g = 0.0;
			materials[curr]->mirrorRef.b = 0.0;
		}
		materialElement = pMaterial->FirstChildElement("PhongExponent");
		if(materialElement != nullptr)
			materialElement->QueryIntText(&materials[curr]->phongExp);

		pMaterial = pMaterial->NextSiblingElement("Material");
	}
	// Parse vertex data
	pElement = pRoot->FirstChildElement("VertexData");
	int cursor = 0;
	Vector3f tmpPoint;
	str = pElement->GetText();
	while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
		cursor++;
	while(str[cursor] != '\0')
	{
		for(int cnt = 0 ; cnt < 3 ; cnt++)
		{
			if(cnt == 0)
				tmpPoint.x = atof(str + cursor);
			else if(cnt == 1)
				tmpPoint.y = atof(str + cursor);
			else
				tmpPoint.z = atof(str + cursor);
			while(str[cursor] != ' ' && str[cursor] != '\t' && str[cursor] != '\n')
				cursor++;
			while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
				cursor++;
		}
		vertices.push_back(tmpPoint);
	}
	// Parse objects
	pElement = pRoot->FirstChildElement("Objects");
	// Parse spheres
	XMLElement *pObject = pElement->FirstChildElement("Sphere");
	XMLElement *objElement;
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int cIndex;
		float R;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Center");
		eResult = objElement->QueryIntText(&cIndex);
		objElement = pObject->FirstChildElement("Radius");
		eResult = objElement->QueryFloatText(&R);

		objects.push_back(new Sphere(id, matIndex, cIndex, R));

		pObject = pObject->NextSiblingElement("Sphere");
	}
	// Parse triangles
	pObject = pElement->FirstChildElement("Triangle");
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int p1Index;
		int p2Index;
		int p3Index;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Indices");
		str = objElement->GetText();
		sscanf(str, "%d %d %d", &p1Index, &p2Index, &p3Index);

		objects.push_back(new Triangle(id, matIndex, p1Index, p2Index, p3Index));

		pObject = pObject->NextSiblingElement("Triangle");
	}
	// Parse meshes
	pObject = pElement->FirstChildElement("Mesh");
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int p1Index;
		int p2Index;
		int p3Index;
		int cursor = 0;
		int vertexOffset = 0;
		vector<Triangle> faces;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Faces");
		objElement->QueryIntAttribute("vertexOffset", &vertexOffset);
		str = objElement->GetText();
		while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
			cursor++;
		while(str[cursor] != '\0')
		{
			for(int cnt = 0 ; cnt < 3 ; cnt++)
			{
				if(cnt == 0)
					p1Index = atoi(str + cursor) + vertexOffset;
				else if(cnt == 1)
					p2Index = atoi(str + cursor) + vertexOffset;
				else
					p3Index = atoi(str + cursor) + vertexOffset;
				while(str[cursor] != ' ' && str[cursor] != '\t' && str[cursor] != '\n')
					cursor++;
				while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
					cursor++;
			}
			faces.push_back(*(new Triangle(-1, matIndex, p1Index, p2Index, p3Index)));
		}

		objects.push_back(new Mesh(id, matIndex, faces));

		pObject = pObject->NextSiblingElement("Mesh");
	}
	// Parse lights
	int id;
	Vector3f position;
	Vector3f intensity;
	pElement = pRoot->FirstChildElement("Lights");

	XMLElement *pLight = pElement->FirstChildElement("AmbientLight");
	XMLElement *lightElement;
	str = pLight->GetText();
	sscanf(str, "%f %f %f", &ambientLight.r, &ambientLight.g, &ambientLight.b);

	pLight = pElement->FirstChildElement("PointLight");
	while(pLight != nullptr)
	{
		eResult = pLight->QueryIntAttribute("id", &id);
		lightElement = pLight->FirstChildElement("Position");
		str = lightElement->GetText();
		sscanf(str, "%f %f %f", &position.x, &position.y, &position.z);
		lightElement = pLight->FirstChildElement("Intensity");
		str = lightElement->GetText();
		sscanf(str, "%f %f %f", &intensity.r, &intensity.g, &intensity.b);

		lights.push_back(new PointLight(position, intensity));

		pLight = pLight->NextSiblingElement("PointLight");

	}
}
