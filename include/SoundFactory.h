#ifndef SOUNDFACTORY_H
# define SOUNDFACTORY_H

# include <vector>
# include <string>
# include <dlfcn.h>
# include "ISound.h"

typedef ISound* (*SoundLoader)();

class SoundFactory
{
public:
	static void load(ISound*& display, int idx);
	static void close(ISound *&display);

private:
	SoundFactory();
	SoundFactory(SoundFactory&);
	~SoundFactory();
	SoundFactory operator=(SoundFactory&);

	static SoundFactory& instance();

	ISound*		doLoad(int);
	void*		_Handle;
	std::vector<std::string> _Libs;
};

#endif
