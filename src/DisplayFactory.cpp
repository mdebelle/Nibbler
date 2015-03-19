#include "DisplayFactory.h"
#include <iostream>

DisplayFactory::DisplayFactory()
{
	_Libs.push_back("lib/ncurses.so");
	_Libs.push_back("lib/opengl.so");
	_Libs.push_back("lib/sfml.so");
}

DisplayFactory& DisplayFactory::instance()
{
	static DisplayFactory fac;

	return fac;
}

DisplayFactory::~DisplayFactory()
{
	if (_Handle && dlclose(_Handle) != 0)
		std::cerr << "Failed to close library: " << dlerror() << std::endl <<
			"Some ressources may have been not deallocated." << std::endl;
}

void	DisplayFactory::load(IDisplay*& display, int idx)
{
	instance()._Handle = dlopen(instance()._Libs.at(idx - 1).c_str(), RTLD_LAZY);
	if (!instance()._Handle)
	{
		std::cerr << "Failed to open library: " << dlerror() << std::endl;
		if (idx != 1)
			load(display, 1);
		else
			exit(-1);
	}

	dlerror(); // Be sure that no error is pending.
	DisplayLoader loader = (DisplayLoader)dlsym(instance()._Handle, "_class_loader");
	char *error = dlerror();
	if (error)
	{
		std::cerr << "Failed to load library: " << error << std::endl;
		exit(-1);
	}
	display = loader();
}

void	DisplayFactory::close(IDisplay*& display)
{
	if (display)
	{
		display->close();
		if (dlclose(instance()._Handle) != 0)
			std::cerr << "Failed to close library: " << dlerror() << std::endl <<
				"Some ressources may have been not deallocated." << std::endl;
		display = nullptr;
		instance()._Handle = nullptr;
	}
}