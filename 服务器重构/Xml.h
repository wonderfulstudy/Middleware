#pragma once
#include "Sensor.h"
#include "stdafx.h"
#include <string>

using namespace std;

class Xml
{
public:
	Xml();
	~Xml();
	Sensor	XmlAnalysis(char *Data);
	void	VersionAnalysis(char *Data);
private:
	string Version;
	string Ver;
	string RecvData;
};

