#include "Menu.h"


Menu::Menu(char *name, bool value) :
	_Name(name),
	_Status(value)
{
	return ;
}

Menu::~Menu()
{
	return ;
}

char	*Menu::getName(void) const
{
	return _Name;
}

bool	Menu::getStatus(void) const
{
	return _Status;
}

void	Menu::SwitchStatus()
{
	_Status = (_Status == true) ? false : true;
	return ;
}
