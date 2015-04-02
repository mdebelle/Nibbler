#ifndef MENU_H
# define MENU_H

class Menu
{

public:
	~Menu();
	Menu(char *name, bool value);

	char		*getName(void) const;
	bool		getStatus(void) const;
	void		SwitchStatus(void);

private:
	Menu();
	Menu(const Menu&);
	Menu&		operator=(const Menu&);

	char		*_Name;
	bool		_Status;
};

#endif
