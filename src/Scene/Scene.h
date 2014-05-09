#ifndef __SCENE_H__
#define __SCENE_H__

#include <iostream>
#include <vector>
#include <math.h>
#include <float.h>
#include <time.h>
#include <string.h>

#include "../MathUtil/RTMath.h"
#include "../Shapes/Shape.h"
#include "../Objects/SceneObject.h"
#include "../Shapes/Sphere.h"
#include "../Shapes/Triangle.h"
#include "../Cameras/Camera.h"
#include "../ImagePlanes/ImagePlane.h"
#include "../Lights/Light.h"
#include "../Lights/PointLight.h"
#include "../Lights/DirectionalLight.h"
#include "../Lights/AmbientLight.h"
#include "../Lights/AreaLight.h"
#include "../Materials/Material.h"
#include "../Transform/MatrixStack.h"
#include "../MathUtil/RTUtil.h"
#include "../Sequence/Sequence.h"
#include "../ImageUtil/Image3ub.h"
#include "../MathUtil/Vec3f.h"
#include "../ImageUtil/TiffEx.h"
#include "../ImageUtil/TextureList.h"

typedef Vec3f Pnt3f;

#define BG_COLOR 0.0,0.0,0.0
#define ERROR_COLOR 255.f,0.f,255.f
#define TEXT_GAP 7
using namespace std;

/*
Main rendering class. Stores all of the assets and manages rendering algorithm and output.
*/

class Scene
{

public:
	Scene(std::string sceneFilename);

	/** CS 148 TODO: Add methods for the scene to render itself, etc. **/

	vector<string> Render();

	void Save(const Image3ub& image, const std::string&);
		
	// Bounce depth
	int depth; 

	// Shadow bias
	float bias; 

	// Antialiasing
	short AASamples;

	// Contains sequence information
	Sequence seq;

	std::string outputFilename;


private:

	Intersection* Intersect(const Ray& r);
	const Color3f Shade(const Intersection*, Ray&, short);
	const Color3f TraceRay(Ray&, short);
	Color3f calcDiffuse(const Color3f&, const Color3f&, Vec3f, Vec3f);
	Color3f calcSpec(const Color3f&, const Color3f&, float, Vec3f, Vec3f, Vec3f);
	
	// Private render methods
	void RenderFrame();
	void RenderSequence();

	/**Console display methods**/
	short getNumDigits(int);
	void printProgress(int, int, int);
	

	/** Parsing helpers **/
	void Parse(std::string sceneFilename);
	void BeganParsing();
	void FinishedParsing();
	void ParsedImageSequence(short numFrames, const Vec3f& distance, const Pnt3f& startLook, const Pnt3f& endLook);
	void ParsedCamera(const Pnt3f& eye, const Vec3f& up, const Pnt3f& lookAt, float fovy, float aspect);
	void ParsedFocus(short, float, const Pnt3f& focPnt);
	void ParsedRackFocus(const Pnt3f& start, const Pnt3f& end);
	void ParsedOutput(int imgWidth, int imgHeight, const std::string& outputFilename);
	void ParsedBounceDepth(int depth);
	void ParsedShadowBias(float bias);
	void ParsedAASamples(short samples);
	void ParsedPushMatrix();
	void ParsedPopMatrix();
	void ParsedRotate(float rx, float ry, float rz);
	void ParsedScale(float sx, float sy, float sz);
	void ParsedTranslate(float tx, float ty, float tz);
	void ParsedSphere(const Pnt3f& center, float radius);
	void ParsedTriangle(const Pnt3f& v1, const Pnt3f& v2, const Pnt3f& v3);
	void ParsedMTriangle(const Pnt3f& v1, const Pnt3f& v2, const Pnt3f& v3, float ua, float va, float ub, float vb, float uc, float vc);
	void ParsedAmbientLight(const Color3f& col);
	void ParsedPointLight(const Pnt3f& loc, const Color3f& col);
	void ParsedDirectionalLight(const Vec3f& dir, const Color3f& col);
	void ParsedAreaLight(const Pnt3f& loc, const Vec3f& v1, const Vec3f& v2, const Color3f& col, short numSamples, float falloff);
	void ParsedMaterial(const Color3f& amb, const Color3f& diff, const Color3f& spec, const Color3f& mirr, float shine);
	void ParsedTexture(const string textureType, const string textureFileName);

	// Instance variables
	ImagePlane plane;
	Camera cam;
	vector<SceneObject*> objects; // TODO: This is a pointer because of my implementation of a shape/object circular reference. Can I change this?
	vector<Material*> materials;

	// Lights
	vector<PointLight> pntLights;
	vector<DirectionalLight> dirLights;
	vector<AmbientLight> ambLights;
	vector<AreaLight> areaLights;


	// Other
	MatrixStack mStack;
	TextureList textures;
	vector<string> fileNames; // Used by display window

};


#endif //__SCENE_H__

