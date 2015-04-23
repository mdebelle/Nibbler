#include "SoundFactory.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

SoundFactory::SoundFactory()
{
	_Libs.push_back("lib/sfaudio.so");
}

SoundFactory& SoundFactory::instance()
{
	static SoundFactory fac;

	return fac;
}

SoundFactory::~SoundFactory()
{
	if (_Handle && dlclose(_Handle) != 0)
		std::cerr << "Failed to close library: " << dlerror() << std::endl <<
			"Some ressources may have been not deallocated." << std::endl;
}

void	SoundFactory::load(ISound*& sound, int idx)
{
	try {
		close(sound);
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	try {
		sound = instance().doLoad(idx);
		sound->init();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		if (idx != 1)
		{
			std::cerr << "Trying with default (" << instance()._Libs[0]
					  << ")..." << std::endl;
			load(sound, 1);
		}
		else
			sound = nullptr;
	}
}

ISound*		SoundFactory::doLoad(int idx)
{
	instance()._Handle = dlopen(instance()._Libs.at(idx - 1).c_str(), RTLD_NOW);
	if (!instance()._Handle)
		throw std::runtime_error(std::string("Failed to open library: ") + dlerror());

	dlerror(); // Be sure that no error is pending.
	SoundLoader loader = (SoundLoader)dlsym(instance()._Handle, "class_loader");
	if (char *error = dlerror())
		throw std::runtime_error(std::string("Failed to load library: ") + error);

	return loader();
}

void	SoundFactory::close(ISound*& sound)
{
	if (sound)
	{
		sound->close();
		delete sound;
		sound = nullptr;
		if (dlclose(instance()._Handle) != 0)
			throw std::runtime_error(std::string("Failed to close library: ") +
				dlerror() + "\nSome ressources may have been not deallocated.\n");
		instance()._Handle = nullptr;
	}
}
