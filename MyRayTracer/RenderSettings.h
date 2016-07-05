#pragma once

#include <string>

#define RENDERSETTINGS RenderSettings::instance() 

class RenderSettings
{

private:
	RenderSettings();

public:
	int width = 450;
	int height = 200;
	int tracerDepth = 5;
	std::string outputFile;
	static RenderSettings * instance();
	~RenderSettings();
};

