#include "NcDisplay.h"

extern "C" IDisplay *class_loader()
{
	return new NcDisplay;
}
