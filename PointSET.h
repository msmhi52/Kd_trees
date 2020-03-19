#ifndef _PoiNTSeT__
#define _PoiNTSeT__

#include "RectHV.h"

#include <set>
#include <vector>

class PointSET{
public:
	PointSET();
	
	bool isEmpty();
	void insert(Point2D p);
	boolean contains(Point2D p);
	void draw();
	vector<Point2D> range(RectHV rect);
	Point2D* nearest(Point2D p);

	int size;
	set<Point2D> p_set;
};

#endif
