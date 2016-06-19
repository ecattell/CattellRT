#include "Material.h"

Material::Material()
{
}

Material::Material(float ra, float ga, float ba,
				   float rd, float gd, float bd,
				   float rs, float gs, float bs,
				   float rr, float gr, float br,
				   float re, float ge, float be,
				   float shininess)
{
	a = Color3f(ra, ga, ba);
	d = Color3f(rd, gd, bd);
	s = Color3f(rs, gs, bs);
	r = Color3f(rr, gr, br);
	rad = Color3f(re, ge, be);
	
	shine = shininess;
	

	initializeDefaultTextures();

}

Material::Material(const Color3f& ambient, const Color3f& diffuse, const Color3f& specular, const Color3f& reflectance, const Color3f& radiosity, float shininess)
{
	a = Color3f(ambient);
	d = Color3f(diffuse);
	s = Color3f(specular);
	r = Color3f(reflectance);
	rad = Color3f(radiosity);

	shine = shininess;

	initializeDefaultTextures();
}

void Material::initializeDefaultTextures()
{
	aTex = dTex = sTex = rTex = radTex = NULL;
}


void Material::setAmbTex(Image3ub* ambTex)
{
	aTex = ambTex; 
}


void Material::setDifTex(Image3ub* difTex)
{
	dTex = difTex;
}

void Material::setSpecTex(Image3ub* specTex)
{
	sTex = specTex;
}

void Material::setReflTex(Image3ub* reflTex)
{
	rTex = reflTex;
}

void Material::setRadTex(Image3ub* radTex)
{
	radTex = radTex;
}

Color3f Material::getAmb(float u, float v) const
{
	if (aTex == NULL) return a;
	else 
	{
		return aTex->Interpolate(u, v);
	}
}


Color3f Material::getDif(float u, float v) const
{
	if (dTex == NULL) return d;
	else 
	{
		return dTex->Interpolate(u, v);
	}
}

Color3f Material::getSpec(float u, float v) const
{
	if (sTex == NULL) return s;
	else 
	{
		return sTex->Interpolate(u, v);
	}
}

Color3f Material::getRefl(float u, float v) const
{
	if (rTex == NULL) return r;
	else 
	{
		return rTex->Interpolate(u, v);
	}
}

Color3f Material::getRadiosity(float u, float v) const
{
	if (rTex == NULL) return rad;
	else 
	{
		return radTex->Interpolate(u, v);
	}
}

float Material::getShine()
{
	return shine;
}


Material::~Material(void)
{
}
