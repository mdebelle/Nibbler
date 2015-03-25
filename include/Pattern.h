#ifndef PATTERN_H
# define PATTERN_H

# include "tools.h"

class	Pattern
{
	public:
		enum Type
		{
			fruit,
			fruit1,
			fruit2,
			fruit3,
			fruit4,
			wall,
			body,
			bodyLU,
			bodyLD,
			bodyRU,
			bodyRD,
			bodyLR,
			bodyUD,
			head,
			headL,
			headR,
			headU,
			headD,

		};

		Pattern(Point position, Type type);
		Pattern(Point position, Point size, Type type);
		Pattern(const Pattern&);

		Pattern&	operator=(const Pattern&);
		virtual		~Pattern();

		Point		get_Position() const;
		Point		get_Size() const;
		Type		get_Type() const;
		bool		get_Visible() const;
		void		set_Position(Point position);
		void		set_Visible(bool);
		void		set_Type(Type t);

	private:
		Point		_Position;
		Point		_Size;
		Type 		_Type;
		bool		_Visible;
		
		Pattern();

};

#endif
