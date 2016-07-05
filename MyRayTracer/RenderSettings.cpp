#include "RenderSettings.h"


RenderSettings * RenderSettings::instance()
{
	
	static RenderSettings instance;
	
	return &instance;

}

RenderSettings::RenderSettings()
{
}


RenderSettings::~RenderSettings()
{
}
