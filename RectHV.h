#ifndef _ReCTHV__
#define _ReCTHV__

#include "Point2D.h"

using namespace std;

class RectHV{
public:
	RectHV(double xmin, double ymin, double xmax, double ymax);

	bool contains(Point2D p);
	bool intersects(RectHV that);
	double distanceTo(Point2D p);
	double distanceSquaredTo(Point2D p);
	
	template <class Object>
	bool equals(Object that){};

//	void draw();
	String toString();

	double xmin;
	double ymin;
	double xmax;
	double ymax;
};

#endif
