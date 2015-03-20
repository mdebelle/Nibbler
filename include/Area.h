#ifndef AREA_H
# define AREA_H

# include "Pattern.h"

class Area
{
	private:
		Point	_Size;

		Area();
		Area(const Area&);
		Area&		operator=(const Area&);

	public:
		Area(Point size);
		~Area();

		int			get_Width() const;
		int			get_Height() const;
		int			get_Area() const;
		Point		get_Size() const;
};

#endif
