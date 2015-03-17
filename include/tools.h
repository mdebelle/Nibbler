#ifndef TOOLS_H
#define TOOLS_H

class Point
{
	Point();

	public:
		Point(int px, int py);
		Point(const Point&);
		Point operator=(const Point&);
		~Point();

		int		x;
		int		y;
};

#endif
