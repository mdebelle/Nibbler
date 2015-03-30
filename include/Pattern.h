#ifndef PATTERN_H
# define PATTERN_H

# include "tools.h"

class	Pattern
{
	public:
		enum Type
		{
			fruit1, fruit2, fruit3, fruit4,
			wall,
			bodyLU, bodyLD, bodyRU, bodyRD, bodyLR, bodyUD,
			headL, headR, headU, headD,
			tailL, tailR, tailU, tailD
		};

		Pattern(Point position, Type type);
		Pattern(const Pattern&);

		Pattern&	operator=(const Pattern&);
		virtual		~Pattern();

		Point		get_Position() const;
		Type		get_Type() const;
		bool		get_Visible() const;
		void		set_Position(Point position);
		void		set_Visible(bool);
		void		set_Type(Type t);

	private:
		Point		_Position;
		Type 		_Type;
		bool		_Visible;
		
		Pattern();
};

#endif
