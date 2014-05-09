// ObjParser.cpp

#include "ObjParser.h"
#include <stdio.h>
#include <iostream>
/*
void ObjParser::addVertex(TriMesh mesh, Vec3f v)
{
	// TODO
}

void ObjParser::addNormal(TriMesh mesh, Vec3f vt)
{
	// TODO
}

void ObjParser::addFace(TriMesh mesh, Vec3f p, Vec3f q, Vec3f r)
{
	// TODO
}

void ObjParser::setMaterialLib(string mtl)
{
	// TODO
}

void ObjParser::useMaterial(string mtr)
{

}

TriMesh ObjParser::generateTriMesh(const FILE * s)
{
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

}
*/