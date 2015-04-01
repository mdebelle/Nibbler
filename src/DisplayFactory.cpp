#include "DisplayFactory.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

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

void	DisplayFactory::load(IDisplay*& display, int idx, int x, int y)
{
	try {
		close(display);
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	try {
		display = instance().doLoad(idx);
		display->init(x, y);
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		if (idx != 1)
		{
			std::cerr << "Trying with default (" << instance()._Libs[0]
					  << ")..." << std::endl;
			load(display, 1, x, y);
		}
		else
			exit(-1);
	}
}

IDisplay*	DisplayFactory::doLoad(int idx)
{
	instance()._Handle = dlopen(instance()._Libs.at(idx - 1).c_str(), RTLD_NOW);
	if (!instance()._Handle)
		throw std::runtime_error(std::string("Failed to open library: ") + dlerror());

	dlerror(); // Be sure that no error is pending.
	DisplayLoader loader = (DisplayLoader)dlsym(instance()._Handle, "class_loader");
	if (char *error = dlerror())
		throw std::runtime_error(std::string("Failed to load library: ") + error);

	return loader();
}

void	DisplayFactory::close(IDisplay*& display)
{
	if (display)
	{
		display->close();
		delete display;
		display = nullptr;
		if (dlclose(instance()._Handle) != 0)
			throw std::runtime_error(std::string("Failed to close library: ") +
				dlerror() + "\nSome ressources may have been not deallocated.\n");
		instance()._Handle = nullptr;
	}
}
