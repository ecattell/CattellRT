// RT.cpp : Defines the entry point for the console application.
//

#include "../MathUtil/RTMath.h"
#include "iostream"
#include <math.h>
#include <string.h>
#include "../MathUtil/RTMath.h"
#include "../Scene/Scene.h"

// TODO: Remove temp includes
#include "../ImageUtil/TiffEx.h"
#include "../ImageUtil/Bmp.h"

using namespace std;

int main(int argc, char** argv);
void usage();


void usage()
{
	cout << "Filename must be argument.\n";
	exit(0);
}

int main(int argc, char** argv)
{

	if (argc != 2)
		usage();
	
	string fileName = string(argv[1]);
	Scene s = Scene(fileName);

	
	vector<string> fileNames = s.Render();
	/*
	//Display window = Display(argc, argv, fileNames);
	*/

	//Image3ub * texture = Bmp::readBmp("../../../textures/test7.bmp");
	//TiffEx::generateTiff(*texture,"../../../output/texturetest.tif");

}
