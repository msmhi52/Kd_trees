#ifndef _KDTRee__
#define _KDTRee__

#include "RectHV.h"

#include <vector>

class node_t{
public:
	node_t();
	node_t(Point2D m_p);
	
private:
	Point2D p;
	RectHV rect;
	node_t* lb;
	node_t* rt;
};

class KdTree{
public:
	KdTree();
	
	bool isEmpty();
	void insert(Point2D p);
	boolean contains(Point2D p);
	void draw();
	vector<Point2D> range(RectHV rect);
	Point2D* nearest(Point2D p);

	set<Point2D> p_set;

private:
	node_t* root;
	int size;
};

#endif
