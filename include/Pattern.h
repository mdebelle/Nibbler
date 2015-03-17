#ifndef PATTERN_H
# define PATTERN_H

# include "tools.h"

class	Pattern
{
	public:
		enum Type
		{
			fruit,
			wall,
			body
		};

		Pattern(Point position, Type type);
		Pattern(Point position, Point size, Type type);
		Pattern(const Pattern&);

		Pattern		operator=(const Pattern&);
		virtual		~Pattern();

		Point		get_Position() const;
		Point		get_Size() const;
		Type		get_Type() const;
		bool		get_Visible() const;
		void		set_Position(Point position);

	private:
		Point		_Position;
		Point		_Size;
		Type 		_Type;
		bool		_visible;
		
		Pattern();

};

#endif
