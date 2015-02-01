#ifndef HELPERS_H_ELE
#define HELPERS_H_ELE

#include "cocos2d.h"

#define RD_PI 3.14159f

namespace rd
{
	std::string strim(std::string str);
	float distance(cocos2d::Point point1, cocos2d::Point point2);
    cocos2d::Vec2 photoshopPixeltoTilePixel(cocos2d::Vec2 vec);
	float RandFloat(float min, float max);
	int RandInt(int min, int max);
	void RandomizeGenerators(float time);
	std::string StringFromInt(int integer);
	std::string encryptString(std::string str);
	std::string decryptString(std::string str);
	std::string atlasName(std::string fileName);
	void limit(float *value, float minVal, float maxVal);
	float RadToDeg(float rad);
	float DegToRad(float deg);
};

#endif