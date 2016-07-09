#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <vector>
#include "../Lights/Light.h"
#include "../Ray/Intersection.h"
#include "../Scene/Scene.h"
#include "../MathUtil/RTUtil.h"
#include "../ImageUtil/Image3ub.h"
#include "../ImageUtil/Color3f.h"
#include "../MathUtil/RTMath.h"

using namespace std;

/*
 * Represents a material. Includes properties for ambient, diffuse, specular, and reflectance and texture information.
 */

class Material
{
public:
	Material();
	Material(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
	Material(const Color3f&, const Color3f&, const Color3f&, const Color3f&, const Color3f&, float, float, float);

	// TODO: Delete this. I implemented this in scene instead.

	virtual ~Material(void);

	// Set textures
	void setAmbTex(Image3ub* ambTex);

	void setDifTex(Image3ub* difTex);

	void setSpecTex(Image3ub* specTex);

	void setReflTex(Image3ub* reflTex);

	void setRadTex(Image3ub* redTex);

	// Get colors values at given uv coordinates
	Color3f getAmb(float u, float v) const;

	Color3f getDif(float u, float v) const;

	Color3f getSpec(float u, float v) const;

	Color3f getRefl(float u, float v) const;

	Color3f getRadiosity(float u, float v) const;

	float getShine() const;
	float getOpacity() const;
	float getRefractionIndex() const;

private:

	void initializeDefaultTextures();

	Color3f a, d, s, r, rad;

	Image3ub *aTex, *dTex, *sTex, *rTex, *radTex;

	float shine;
	float opacity;
	float refractionIndex;
};

#endif //__MATERIAL_H__
