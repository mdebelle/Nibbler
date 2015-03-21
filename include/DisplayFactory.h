#ifndef DISPLAYFACTORY_H
# define DISPLAYFACTORY_H

# include <vector>
# include <string>
# include <dlfcn.h>
# include "IDisplay.h"

typedef IDisplay* (*DisplayLoader)();

class DisplayFactory
{
public:
	static void load(IDisplay*& display, int idx);
	static void close(IDisplay *&display);

private:
	DisplayFactory();
	DisplayFactory(DisplayFactory&);
	~DisplayFactory();
	DisplayFactory operator=(DisplayFactory&);

	static DisplayFactory& instance();

	IDisplay*	doLoad(int);
	void*	_Handle;
	std::vector<std::string> _Libs;
};

#endif
