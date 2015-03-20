#include "SfDisplay.h"

extern "C" IDisplay *class_loader()
{
	return new SfDisplay;
}
