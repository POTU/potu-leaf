#include "Helpers.h"

namespace rd
{
	float distance(cocos2d::Point point1, cocos2d::Point point2)
	{
		double distanceVar = sqrt(((point2.x-point1.x)*(point2.x-point1.x)) + ((point2.y-point1.y)*(point2.y-point1.y)));
		float returnDistance = (float)distanceVar;
		return distanceVar;
	}

	float RandFloat(float min, float max)
	{
		assert(max > min); 
		float random = ((float) rand()) / (float) RAND_MAX;

		float range = max - min;  
		return (random*range) + min;
	}

	int RandInt(int min, int max)
	{
		assert(max > min); 
		float randfloat = RandFloat((float)min, (float)max);
		randfloat = randfloat + 0.5f;
		int intConversion = (int)randfloat;
		return intConversion;
	}

	void RandomizeGenerators(float time)
	{
		srand((int)time);
	}

	std::string encryptString(std::string str)
	{
		std::string plainStr = str;

		return plainStr;
	}

	std::string decryptString(std::string str)
	{
		std::string cryptedStr = str;

		return cryptedStr;
	}

	std::string StringFromInt(int integer)
	{
		std::stringstream strStream;
		strStream << integer;
		std::string str;
		strStream >> str;
		return str;
	}

	std::string atlasName(std::string fileName)
	{
		std::string tmpName = fileName;
		float scaleFactor = cocos2d::Director::getInstance()->getContentScaleFactor();

		std::string end = "";

		if(scaleFactor == 0.25f) end = "SD.atlas";
		else if(scaleFactor == 0.5f) end = "HD.atlas";
		else end = "HDR.atlas";

		std::string endingStr = tmpName+end;
		return endingStr;
	}

	std::string strim(std::string str)
	{
		std::string tmp = str;
		std::stringstream trimmer;
		trimmer << tmp;
		tmp.clear();
		trimmer >> tmp;
		return tmp;
	}

	void limit(float *value, float minVal, float maxVal)
	{
		float tmpVal = *value;
		if(tmpVal < minVal) tmpVal = minVal;
		if(tmpVal > maxVal) tmpVal = maxVal;
		*value = tmpVal;
	}

	float RadToDeg(float rad)
	{
		float deg = (rad/(2*RD_PI))*360.0;
		return deg;
	}
	float DegToRad(float deg)
	{
		float rad = (deg/360.0)*(2*RD_PI);
		return rad;
	}
};

