#include "GlDisplay.h"

extern "C" IDisplay *class_loader()
{
	return new GlDisplay;
}
