#include "SfSound.h"

extern "C" ISound *class_loader()
{
	return new SfSound;
}
