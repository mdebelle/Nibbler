#ifndef PATTERN_H
# define PATTERN_H

# include "tool.h"

class	Pattern
{
	enum Type
	{
		fruit,
		wall,
		body
	};

	Point	_Position;
	Point	_Size
	Type 	_Type;
	
	Pattern();

	public:
		Pattern(Point position, Type type);
		Pattern(Point position, Point size, Type type);
		Pattern(Pattern&);

		Pattern		operator=(Pattern&);
		virtual 	~Pattern();

		Point		get_Position() const;
		Point		get_Size() const;
		Type		get_Type() const;
		void		set_Position(Point position);

};

#endif
