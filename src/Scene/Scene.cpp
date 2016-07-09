#include "Scene.h"
#include <fstream>
#include <sstream>

Scene::Scene(std::string sceneFilename)
{
	cout << "Loading: " << sceneFilename << "\n";
	Parse(sceneFilename);

}

void Scene::Parse(std::string sceneFilename)
{
	BeganParsing();

	std::ifstream sceneFile(sceneFilename.c_str());

	// Die if we couldn't find the file
	if (sceneFile.fail())
	{
		printf("Scene::Parse - Could not find input scene file '%s'\n", sceneFilename.c_str());
		exit(1);
	}

	char line[1024];
	while (!sceneFile.eof())
	{
		sceneFile.getline(line, 1023);
		std::stringstream ss;
		ss.str(line);
		std::string command;
		ss >> command;

		if (command == "Camera")
		{
			float ex, ey, ez, ux, uy, uz, lx, ly, lz, f, a;
			ss >> ex >> ey >> ez >> ux >> uy >> uz >> lx >> ly >> lz >> f >> a;
			Pnt3f eye(ex, ey, ez);
			Vec3f up(ux, uy, uz);
			Pnt3f lookAt(lx, ly, lz);
			ParsedCamera(eye, up, lookAt, f, a);
		}
		else if (command == "Output")
		{
			int w, h;
			std::string fname;
			ss >> w >> h >> fname;
			ParsedOutput(w, h, fname);
		}
		else if (command == "ImageSequence")
		{
			short numFrames;
			float distanceX, distanceY, distanceZ, startLookX, startLookY, startLookZ, endLookX, endLookY, endLookZ;
			ss >> numFrames >> distanceX >> distanceY >> distanceZ >> startLookX >> startLookY >> startLookZ >> endLookX >> endLookY >> endLookZ;
			ParsedImageSequence(numFrames, Vec3f(distanceX, distanceY, distanceZ), Pnt3f(startLookX, startLookY, startLookZ), Pnt3f(endLookX, endLookY, endLookZ));
		}
		else if (command == "RackFocus")
		{
			float pntStartX, pntStartY, pntStartZ, pntEndX, pntEndY, pntEndZ;
			ss >> pntStartX >> pntStartY >> pntStartZ >> pntEndX >> pntEndY >> pntEndZ;
			ParsedRackFocus(Pnt3f(pntStartX, pntStartY, pntStartZ),Pnt3f(pntEndX, pntEndY, pntEndZ));
		}
		else if (command == "Focus")
		{
			short numDOFSamples;
			float apertureSize, focPntX, focPntY, focPntZ;
			ss >> numDOFSamples >> apertureSize >> focPntX >> focPntY >> focPntZ;
			ParsedFocus(numDOFSamples, apertureSize, Pnt3f(focPntX, focPntY, focPntZ));
		}
		else if (command == "BounceDepth")
		{
			int depth;
			ss >> depth;
			ParsedBounceDepth(depth);
		}
		else if (command == "GIDepth")
		{
			int giDepth;
			ss >> giDepth;
			ParsedGIDepth(giDepth);
		}
		else if (command == "GISamples")
		{
			short samples;
			ss >> samples;
			ParsedGISamples(samples);
		}
		else if (command == "ShadowBias")
		{
			float bias;
			ss >> bias;
			ParsedShadowBias(bias);
		}
		else if (command == "AASamples")
		{
			short samples;
			ss >> samples;
			ParsedAASamples(samples);
		}
		else if (command == "PushMatrix")
		{
			ParsedPushMatrix();
		}
		else if (command == "PopMatrix")
		{
			ParsedPopMatrix();
		}
		else if (command == "Rotate")
		{
			float rx, ry, rz;
			ss >> rx >> ry >> rz;
			ParsedRotate(rx, ry, rz);
		}
		else if (command == "Scale")
		{
			float sx, sy, sz;
			ss >> sx >> sy >> sz;
			ParsedScale(sx, sy, sz);
		}
		else if (command == "Translate")
		{
			float tx, ty, tz;
			ss >> tx >> ty >> tz;
			ParsedTranslate(tx, ty, tz);
		}
		else if (command == "Sphere")
		{
			float cx, cy, cz, r;
			ss >> cx >> cy >> cz >> r;
			Pnt3f center(cx, cy, cz);
			ParsedSphere(center, r);
		}
		else if (command == "Triangle")
		{
			float x1, y1, z1, x2, y2, z2, x3, y3, z3;
			ss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			Pnt3f v[3]; // TODO: Why should I prepackage this in a point (here and below)?
			v[0] = Pnt3f(x1, y1, z1);
			v[1] = Pnt3f(x2, y2, z2);
			v[2] = Pnt3f(x3, y3, z3);
			ParsedTriangle(v[0], v[1], v[2]);
		}
		else if (command == "MTriangle")
		{
			float x1, y1, z1, x2, y2, z2, x3, y3, z3, ua, va, ub, vb, uc, vc;
			ss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3 >> ua >> va >> ub >> vb >> uc >> vc;
			Pnt3f v[3];
			v[0] = Pnt3f(x1, y1, z1);
			v[1] = Pnt3f(x2, y2, z2);
			v[2] = Pnt3f(x3, y3, z3);
			ParsedMTriangle(v[0], v[1], v[2], ua, va, ub, vb, uc, vc);
		}
		else if (command == "AmbientLight")
		{
			float r, g, b;
			ss >> r >> g >> b;
			Color3f col(r, g, b);
			ParsedAmbientLight(col);
		}
		else if (command == "PointLight")
		{
			float px, py, pz, r, g, b;
			ss >> px >> py >> pz >> r >> g >> b;
			Pnt3f pos(px, py, pz);
			Color3f col(r, g, b);
			ParsedPointLight(pos, col);
		}
		else if (command == "DirectionalLight")
		{
			float dx, dy, dz, r, g, b;
			ss >> dx >> dy >> dz >> r >> g >> b;
			Vec3f dir(dx, dy, dz);
			Color3f col(r, g, b);
			ParsedDirectionalLight(dir, col);
		}
		else if (command == "AreaLight")
		{
			float px, py, pz, v1x, v1y, v1z, v2x, v2y, v2z, r, g, b, falloff;
			short numSamples;
			ss >> px >> py >> pz >> v1x >> v1y >> v1z >> v2x >> v2y >> v2z >> numSamples >> falloff >> r >> g >> b;
			Pnt3f loc(px,py,pz);
			Vec3f v1(v1x,v1y,v1z);
			Vec3f v2(v2x,v2y,v2z);
			Color3f col(r, g, b);
			ParsedAreaLight(loc,v1,v2,col,numSamples,falloff);
		}
		else if (command == "Material")
		{
			float ra, ga, ba, rd, gd, bd, rs, gs, bs, rr, gr, br, rRad, gRad, bRad, shine;
			ss >> ra >> ga >> ba >> rd >> gd >> bd >> rs >> gs >> bs >> rr >> gr >> br >> rRad >> gRad >> bRad >> shine;
			Color3f amb(ra, ga, ba);
			Color3f diff(rd, gd, bd);
			Color3f spec(rs, gs, bs);
			Color3f mirr(rr, gr, br);
			Color3f radiosity(rRad, gRad, bRad);
			ParsedMaterial(amb, diff, spec, mirr, radiosity, shine, 1, 1);
		}
		else if (command == "rMaterial")
		{
			float ra, ga, ba, rd, gd, bd, rs, gs, bs, rr, gr, br, rRad, gRad, bRad, shine, refractIndex, opacity;
			ss >> ra >> ga >> ba >> rd >> gd >> bd >> rs >> gs >> bs >> rr >> gr >> br >> rRad >> gRad >> bRad >> shine >> refractIndex >> opacity;
			Color3f amb(ra, ga, ba);
			Color3f diff(rd, gd, bd);
			Color3f spec(rs, gs, bs);
			Color3f mirr(rr, gr, br);
			Color3f radiosity(rRad, gRad, bRad);
			ParsedMaterial(amb, diff, spec, mirr, radiosity, shine, refractIndex, opacity);
		}
		else if (command == "Texture")
		{
			string textureType,textureFileName;
			ss >> textureType >> textureFileName;
			ParsedTexture(textureType,textureFileName);			
		}
	}
	sceneFile.close();

	FinishedParsing();

}

void Scene::BeganParsing()
{
	// TODO: These are no longer used
	/*
	vector<PointLight> pntLights = vector<PointLight>();
	vector<DirectionalLight> dirLights = vector<DirectionalLight>();;
	vector<AmbientLight> ambLights = vector<AmbientLight>();;
	vector<AreaLight> areaLights = vector<AreaLight>();;
	vector<SceneObject> objects = vector<SceneObject>();
	vector<Material> materials = vector<Material>();
	*/
	MatrixStack mStack = MatrixStack(); // TODO: Why is matrixStack declared here again?
	textures = TextureList();

	// Set defaults
	AASamples = 1;
	giSamples = 0;
	giDepth   = 0;
	seq = Sequence(false);

	// Used by window manager for displaying:
	//vector<string> fileNames = vector<string>();

	//TODO: In fact, why does it appear that everything is declared again?
}

void Scene::FinishedParsing()
{
	// Seed random number generator
	srand(time(NULL));

	// Initialize camera
	cam.Initialize(plane.getWidthSamples(),plane.getHeightSamples());
	
	// Initialize BVH
	accelerator = BVH(this->objects, 'x');
}

void Scene::ParsedImageSequence(short numFrames, const Vec3f& distance, const Pnt3f& startLook, const Pnt3f& endLook)
{
	seq = Sequence(true,numFrames,distance,startLook,endLook);
}

void Scene::ParsedCamera(const Pnt3f& _loc, const Vec3f& _up, const Pnt3f& _lookAt, float _fovy, float _aspect)
{
	cam = Camera(_loc, _up, _lookAt, _fovy, _aspect);
}

void Scene::ParsedFocus(short _numDOFSamples, float _apertureSize, const Pnt3f& _focPnt)
{
	cam.setFocus(_numDOFSamples, _apertureSize, _focPnt);
}

void Scene::ParsedRackFocus(const Pnt3f& start, const Pnt3f& end)
{
	seq.RackFocus(start, end);
}

void Scene::ParsedOutput(int _imgWidth, int _imgHeight, const std::string& _outputFilename)
{
	plane = ImagePlane(_imgWidth, _imgHeight);
	outputFilename = _outputFilename;
}

void Scene::ParsedBounceDepth(int _depth)
{
	depth = _depth;
}

void Scene::ParsedGIDepth(int _giDepth)
{
	giDepth = _giDepth;
}

void Scene::ParsedShadowBias(float _bias)
{
	bias = _bias;
}

void Scene::ParsedAASamples(short samples)
{
	AASamples = samples;
}

void Scene::ParsedGISamples(short samples)
{
	giSamples = samples;
}

void Scene::ParsedPushMatrix()
{
	mStack.push();
}

void Scene::ParsedPopMatrix()
{
	mStack.pop();
}

void Scene::ParsedRotate(float rx, float ry, float rz)
{
	mStack.rotate(convertToRadians(rx),convertToRadians(ry),convertToRadians(rz));
}

void Scene::ParsedScale(float sx, float sy, float sz)
{
	mStack.scale(sx,sy,sz);
}

void Scene::ParsedTranslate(float tx, float ty, float tz)
{
	mStack.translate(tx,ty,tz);
}

void Scene::ParsedSphere(const Pnt3f& center, float radius)
{
	Sphere * sphr = new Sphere(center,radius,mStack.getTop());
	SceneObject * obj = new SceneObject(sphr, materials.back(), mStack.getTop());
	sphr->setSceneObject(obj);
	objects.push_back(obj);
}

void Scene::ParsedTriangle(const Pnt3f& v1, const Pnt3f& v2, const Pnt3f& v3)
{
	Triangle * tri = new Triangle(v1,v2,v3,mStack.getTop());
	SceneObject* obj = new SceneObject(tri, materials.back(), mStack.getTop());
	tri->setSceneObject(obj);
	objects.push_back(obj);
}

void Scene::ParsedMTriangle(const Pnt3f& v1, const Pnt3f& v2, const Pnt3f& v3, float ua, float va, float ub, float vb, float uc, float vc)
{
	Triangle * tri = new Triangle(v1,v2,v3,mStack.getTop(),ua,va,ub,vb,uc,vc);
	SceneObject* obj = new SceneObject(tri, materials.back(), mStack.getTop());
	tri->setSceneObject(obj);
	objects.push_back(obj);
}
			

void Scene::ParsedAmbientLight(const Color3f& col)
{
	ambLights.push_back(AmbientLight(col));
}

void Scene::ParsedPointLight(const Pnt3f& loc, const Color3f& col)
{
	pntLights.push_back(PointLight(loc,col));
}

void Scene::ParsedDirectionalLight(const Vec3f& dir, const Color3f& col)
{
	dirLights.push_back(DirectionalLight(dir,col));
}

void Scene::ParsedAreaLight(const Pnt3f& loc, const Vec3f& v1, const Vec3f& v2, const Color3f& col, short numSamples, float falloff)
{
	areaLights.push_back(AreaLight(loc, v1, v2, col, numSamples, falloff));
}

void Scene::ParsedMaterial(const Color3f& amb, const Color3f& diff, const Color3f& spec, const Color3f& mirr, const Color3f& radiosity, float shine, float refractIndex, float opacity)
{
	Material* mat = new Material(amb,diff,spec,mirr,radiosity,shine, refractIndex, opacity);
	materials.push_back(mat);

}

void Scene::ParsedTexture(const string textureType, const string textureFileName)
{
	if (materials.back() == NULL)
	{
		cout << "Error importing texture. Material must be declared prior to texture.\n";
		return;
	}
	// Check texture list for texture with given filename.
	// Textures class returns pointer to existing texture if texture already in list.
	// Otherwise, it creates new entry and returns pointer to texture.
	if (textureType == "Ambient")
	{
		materials.back()->setAmbTex( textures.add(textureFileName) );
	}
	else if (textureType == "Diffuse")
	{
		materials.back()->setDifTex( textures.add(textureFileName) );
	}
	else if (textureType == "Specular")
	{
		materials.back()->setSpecTex( textures.add(textureFileName) );
	}
	else if (textureType == "Reflective")
	{
		materials.back()->setReflTex( textures.add(textureFileName) );
	}
	else if (textureType == "Radiosity")
	{
		materials.back()->setRadTex( textures.add(textureFileName) );
	}
	else
	{
		cout << "Error importing texture. Texture type must be Ambient, Diffuse, Specular, or Reflective\n";
		return;
	}

}

short Scene::getNumDigits(int num)
{
	int dig = 0;
	while (num) {
		num /= 10;
		dig++;
	}
	return dig;
}

void Scene::printProgress(int startTime, int x, int w)
{
	float percent = ((float)x/(float)w);
	int displayPercent = floor(percent*100+.5);
	cout << displayPercent << "%";
	int currTime = time(NULL);
	int secondsElapsed = currTime - startTime;
	int totalEstimatedTime = secondsElapsed / percent;
	int remainingTime = totalEstimatedTime - secondsElapsed;

	int secElapsed = secondsElapsed%60;
	int minElapsed = secondsElapsed/60;

	int seconds = remainingTime%60;
	int minutes = remainingTime/60;

	short gapSize1 = TEXT_GAP - getNumDigits(displayPercent);
	short gapSize2 = TEXT_GAP - getNumDigits(secElapsed) - getNumDigits(minElapsed);

	string gap1 = "";
	for (int i = 0; i < gapSize1; i++)
	{
		gap1 = gap1 + " ";
	}

	string gap2 = "";
	for (int i = 0; i < gapSize2; i++)
	{
		gap2 = gap2 + " ";
	}

	cout << gap1 << "Elapsed: " << minElapsed << "m " << secElapsed << "s" << gap2 << " Est remaining: " << minutes << " m " << seconds << "s" << "\n";
}

// Loops over all samples of the image plane and computes a color for each pixel
void Scene::RenderFrame()
{

	cout << "\nRendering Image\n";

	// Computes the origin and direction of each viewing ray for each pixel
	int w = plane.getWidthSamples();
	int h = plane.getHeightSamples();

	Image3ub image = Image3ub(w,h,Color3ub(ERROR_COLOR));

	int startTime = time(NULL);
	int prevProgressOutput = startTime;
	// get current time
	for (int x = 0; x < w; x++)
	{
		int currTime = time(NULL);
		if ((currTime - prevProgressOutput > 10)) // Print progress
		{
			prevProgressOutput = currTime;
			printProgress(startTime, x, w);
		}
		for (int y = 0; y < h; y++)
		{
			// Don't jitter if only one sample
			if (AASamples <= 1 && cam.DOF == false)
			{
				Ray viewRay = cam.generateViewRay(x,y);
				Color3f traceCol = TraceRay(viewRay,0,0);
				image.SetPixel(x,y,Color3ub(traceCol));
			}
			else
			{ // Stratified sampling for antialiasing
				Color3f c = Color3f(0.f,0.f,0.f);
				for (int p = 0; p < AASamples; p++){
					for (int q = 0; q < AASamples; q++) {
						float xPrime, yPrime;

						if (AASamples != 1) // don't use AA if there aren't enough samples
						{
							xPrime = x + (p + randFloat()) / AASamples; // What if I subtract .5 from randFloat?
							yPrime = y + (q + randFloat()) / AASamples;
						}
						else
						{
							xPrime = x;
							yPrime= y;
						}

						// Generate extra samples for DOF
						Ray viewRay = cam.generateViewRay(xPrime,yPrime);
						if (cam.DOF == false) c += TraceRay(viewRay,0,0);
						else {
							for (int i = 0; i < cam.getSamples(); i++)
							{
								for (int j = 0; j < cam.getSamples(); j++)
								{
									Ray DOFRay = cam.defocusRay(viewRay,i,j);
									c += TraceRay(DOFRay,0,0);
								}
							}
						}

					}
				}
				c = c/(AASamples*AASamples*(cam.getSamples()*cam.getSamples()));
				image.SetPixel(x,y,Color3ub(c));
			}
		}
	}

	cout << "Render complete\n\n";
	int currTime  = time(NULL);
	int elapsed   = currTime - startTime;
	cout << "Time elapsed: " << elapsed << "\n";
	Save(image, outputFilename);
	fileNames.push_back(string(outputFilename));
}

// Traces a viewing ray for a single sample in the image plane.
// Also invoked for computing recursive reflections.
const Color3f Scene::TraceRay(Ray& r, short numReflections, short giBounces)
{

	Intersection* i = Intersect(r);
	if (i != NULL)
	{	
		Color3f returnColor = Shade(i,r,numReflections, giBounces); // Color3f(i->normal.x,i->normal.y,i->normal.z);//
		delete i;
		return returnColor; 
	}
	else
	{
		return Color3f(BG_COLOR);
	}
}



// Intersects a ray with the scene, returns an intersection object with
// details about the intersection. If it doesn't it anything, returns a null pointer.
// Also used when tracing shadow rays.
Intersection* Scene::Intersect(const Ray& r)
{
	return accelerator.hit(r);
}

// Calculates the color contribution of the given light
const Color3f Scene::getLightColorContribution(const Intersection * i, Light& light, Ray& viewingRay)
{
	Pnt3f intersectPnt  = i->loc;
	
	Vec3f lightDir = light.getDir(intersectPnt);
	if (SameDirection(lightDir,i->normal))
	{
		// Ignore this light if normal and light are pointed in opposite directions.
		return Color3f(0.0,0.0,0.0);
	}
	else
	{
		// Get distance to light
		// Note: This is slightly inefficient, as this operation has some redundancy with light->getDir().
		float lightDist  = light.getDist(intersectPnt);
		
		Ray toLight = Ray(intersectPnt, lightDir, bias, lightDist);
		
		// Check if the light is not blocked by another object.
		Intersection* toLightIntersect = Intersect(toLight);
		
		Color3f resultColor = Color3f(0.0,0.0,0.0);
		
		if (toLightIntersect == NULL)
		{
			Material* m = i->obj->m;
			Vec3f Lm = toLight.d;
			Lm.Normalize(); // TODO optimization: Is this already normalized?
			Color3f lightColor = light.color;
			resultColor += calcDiffuse(lightColor, m->getDif(i->u,i->v), Lm, i->normal);
			resultColor += calcSpec(lightColor, m->getSpec(i->u,i->v), m->getShine(), viewingRay.d, Lm, i->normal);
		}	
		else 
		{
			//TODO implement transparency?
			delete toLightIntersect;
		}
		
		return resultColor;
	}
}

// set pixel color to value computed from point, lights, viewing direction, and normal
const Color3f Scene::Shade(const Intersection * i, Ray& viewingRay, short numReflections, short giBounces=1)
{

	Material* m = i->obj->m;

	Color3f resultColor = Color3f(0.0,0.0,0.0);

	// For each ambient light, add color
	if (SameDirection(viewingRay.d,i->normal)){ // Cull backface objects
		for(std::vector<AmbientLight>::iterator it = ambLights.begin(); it != ambLights.end(); ++it) {
			resultColor += it->color*m->getAmb(i->u,i->v);
		}
	}
	Pnt3f intersectPnt = i->loc;

	// For each point light, calculate diffuse and specular
	for(std::vector<PointLight>::iterator it = pntLights.begin(); it != pntLights.end(); ++it) {
		PointLight light = *it;
		resultColor += getLightColorContribution(i, light, viewingRay);
	}

	// For each directional light, calculate diffuse and specular
	for(std::vector<DirectionalLight>::iterator it = dirLights.begin(); it != dirLights.end(); ++it) {
		DirectionalLight light = *it;
		resultColor += getLightColorContribution(i, light, viewingRay);
	}
	
	// For each area light, calculate diffuse and specular
	for(std::vector<AreaLight>::iterator it = areaLights.begin(); it != areaLights.end(); ++it) {
		// Component of lighting from this area light.
		Color3f areaColor = Color3f(0.f,0.f,0.f);
		AreaLight light = *it;
		// TODO: I should implement jittered sampling like in my AASampler (Shirley page 312)
		// Pass in two new color/specular N times where N is num samples
		int numSamples = light.getNumSamples();
		for (int j = 0; j < numSamples; j++)
		{
			for (int k = 0; k < numSamples; k++)
			{
				light.updateSample(j,k);
				areaColor += getLightColorContribution(i, light, viewingRay);
			}
		}
		// Calculate average influence of each sample
		areaColor = areaColor/(numSamples*numSamples);

		// Add new light to total
		resultColor += areaColor;
	}

	// Calculate reflectance
	// EXPANSION TODO: I can examine roughness here and take multiple samples if I implement roughness.
	Color3f reflectMaterial = m->getRefl(i->u,i->v);
	if (numReflections < depth && RTMin(RTMin(reflectMaterial.r,reflectMaterial.g),reflectMaterial.b) > FLT_EPSILON) // 
	{
		Vec3f reflectDir = reflectVec(viewingRay.d,i->normal);
		Ray reflectRay = Ray(Pnt3f(i->loc), reflectDir, bias, FLT_MAX); // TODO: Can I do this without defining a new point here?
		resultColor += TraceRay(reflectRay,numReflections++,giBounces)*m->getRefl(i->u,i->v);
	}
	
	// Calculate GI
	resultColor += addGIComponent(i, numReflections, giBounces);
	
	// Calculate refraction
	// m, 
	float opacity = m->getOpacity();
	if (opacity < 1-FLT_EPSILON)
	{
		float rIndex = m->getRefractionIndex();
		Vec3f refractDir = refractVec(viewingRay.d, i->normal, rIndex);
		Ray refractRay = Ray(Pnt3f(i->loc), refractDir, bias, FLT_MAX);
		//std::cout << "Calculating refraction\n";
		Color3f result = TraceRay(refractRay,numReflections,giBounces); // TODO weigh refraction? ///Color3f(1.0f, 0.f, 0.f);
		resultColor = result + resultColor*opacity; 
	}
	
	return resultColor;
}

const Vec3f Scene::refractVec(const Vec3f& incidentVec, const Vec3f& normal, float rIndex)
{
	float c1 = -Vec3f::Dot(normal, incidentVec);
	Vec3f Rl = incidentVec + (2 * normal * c1 );
	
	// Determine change in refraction index
	float rOrigMedium;
	float rNewMedium;
	if (c1 > 0.f) // if leaving
	{
		rOrigMedium = rIndex; // original medium
		rNewMedium = 1.f; // new medium
	}
	else // if entering
	{
		rOrigMedium = 1.f;
		rNewMedium  = rIndex;
	}
	float r = rNewMedium / rOrigMedium;
	float c2 = sqrtf(1 - r*r * (1-c1*c1));
	Vec3f result = (r * incidentVec) + (r * c1 - c2) * normal;
	return result;
}

const Vec2f Random2DDir()
{
	float azimuth = randFloat() * M_PI * 2;
	return Vec2f(cos(azimuth), sin(azimuth));
}

// Should provide uniform distribution
const Vec3f randomUnitVector()
{
	float z = (2*randFloat()) - 1; // z is in the range [-1,1]
	Vec2f planar = Random2DDir() * sqrt(1-z*z);
	return Vec3f(planar.x, planar.y, z);
}

const Vec3f randomInHemisphere(Vec3f const &v){
	Vec3f resultVec = randomUnitVector();
	
	// If the resulting vector is pointing in the opposite direction, flip it
	if(Vec3f::Dot(v,resultVec)<0){
		resultVec.x= -resultVec.x;
		resultVec.y= -resultVec.y;
		resultVec.z= -resultVec.z;
	}
	return resultVec;
}

const Color3f Scene::addGIComponent(const Intersection * intersect, short numReflections, short giBounces)
{
	if (giSamples > 0 && giBounces < giDepth) {
		giBounces++;

		Color3f giColor = Color3f(0.0,0.0,0.0);
		Material* m = intersect->obj->m;
		Color3f radiosity = m->getRadiosity(intersect->u,intersect->v);
	 
		// cout << radiosity.r;
		// cout << radiosity.g;
		// cout << radiosity.b;
		
		// Get normal at hit
		Vec3f hitNormal = intersect->normal;
		
		Color3f bouncedLight = Color3f(0.0,0.0,0.0);
		// for each sample
		for (int i = 0; i < giSamples; i++)
		{
			//Get random direction in same hemisphere as normal
			Vec3f dir = randomInHemisphere(hitNormal);			
			Ray r = Ray ( intersect->loc, dir, bias, FLT_MAX );
			bouncedLight += TraceRay(r, numReflections, giBounces);
		}
		bouncedLight = bouncedLight / giSamples;
		
		return radiosity*bouncedLight;
	}
	else {
		// Return black if max giBounces reached
		return Color3f(0.0,0.0,0.0);
	}
	
	/*
	//TODO
	if (emittance > Color3f(FLT_EPSILON,FLT_EPSILON,FLT_EPSILON))
	{
		// Pick a random direction from here and keep going.
		Ray newRay;
		newRay.origin = r.pointWhereObjWasHit;
		newRay.direction = RandomUnitVectorInHemisphereOf(r.normalWhereObjWasHit);  // This is NOT a cosine-weighted distribution!
	   
		// Compute the BRDF for this ray (assuming Lambertian reflection)
		float cos_theta = DotProduct(newRay.direction, r.normalWhereObjWasHit);
		Color BRDF = 2 * m.reflectance * cos_theta;
		Color reflected = TracePath(newRay, depth + 1);
		
		// Apply the Rendering Equation here.
		result = emittance + (BRDF * reflected);
	}
	return giColor;
	*/

}

Color3f Scene::calcDiffuse(const Color3f& lightColor, const Color3f& diffuse, Vec3f Lm, Vec3f normal)
{
	return Color3f ( (diffuse/Lm.Length() * lightColor) * RTMax(Vec3f::Dot(Lm,normal),0.f) );
}

Color3f Scene::calcSpec(const Color3f& lightColor, const Color3f& specular, float shine, Vec3f viewingRayDir, Vec3f Lm, Vec3f normal)
{	
	// Uses blinn-phong for specular
	Vec3f h = (Lm-viewingRayDir);
	h.Normalize();
	return Color3f( specular * lightColor * pow( RTMax(0.f,Vec3f::Dot(normal,h)), shine) );
}

void Scene::Save(const Image3ub& image, const std::string& fileName)
{
	TiffEx exporter = TiffEx();
	exporter.generateTiff(image, fileName);

	cout << "File saved to: " << fileName << "\n";
}

vector<string> Scene::Render(){

	if (seq.isSequence == true)
	{
		RenderSequence();
	}
	else RenderFrame();

	return fileNames;
}

void Scene::RenderSequence()
{
	string sequenceBaseFilename = string(outputFilename);
	sequenceBaseFilename = sequenceBaseFilename.substr(0,sequenceBaseFilename.find("."));
	//Pnt3f lookAtStart = Pnt3f(startLookX,startLookY,startLookZ);
	//Pnt3f endLook = Pnt3f(endLookX,endLookY,endLookZ);
	Pnt3f moveStart = cam.getPos();
	//Vec3f moveVector = Vec3f(distanceX,distanceY,distanceZ); //Vec3f(distanceX,distanceY,distanceZ);
	ostringstream convert;

	int startTime = time(NULL);
	for (int i = 0; i < seq.numFrames; i++)
	{
		// Print progress
		if (i != 0)
		{
			float percent = ((float)i/(float)seq.numFrames);
			int displayPercent = floor(percent*100+.5);
			cout << "Sequence progress: " << displayPercent << "%\n";
			int currTime = time(NULL);
			int secondsElapsed = currTime - startTime;
			int totalEstimatedTime = secondsElapsed / percent;
			int remainingTime = totalEstimatedTime - secondsElapsed;

			int secElapsed = secondsElapsed%60;
			int minElapsed = secondsElapsed/60;
			int hoursElapsed = minElapsed/60;
			minElapsed = minElapsed%60;

			int seconds = remainingTime%60;
			int minutes = remainingTime/60;

			int hours = minutes/60;
			minutes = minutes%60;

			cout << "Total time elapsed: " << hoursElapsed << "h " << minElapsed << "m " << secElapsed << "s" << "\n" << "Total est remaining: " << hours << "h " << minutes << "m " << seconds << "s" << "\n";
		}

		cout << "\nFrame #" << i << "\n";
		float t = cos((((float)i)/seq.numFrames+1)*M_PI)/2+.5; // Use sin wave to interpolate movement
		Pnt3f newLocation = moveStart+seq.distance*t;
		cam.Move(newLocation);
		Pnt3f newLook = seq.startLook*(1-t)+seq.endLook*t;
		cam.Pan(newLook);
		
		// Rack focus if necessary
		if (cam.DOF == true)
		{
			Pnt3f newFocus = seq.startFocus*(1-t)+seq.endFocus*t;
			cam.setFocusPoint(newFocus);
		}

		convert.str(std::string());
		convert << i;
		outputFilename = string(sequenceBaseFilename);
		outputFilename.append(convert.str() + ".tif"); // TODO: should I save the extension somewhere and paste it back on, instead of hardcoding this in?
		RenderFrame();
	}
}
