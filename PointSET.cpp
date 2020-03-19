#include "PointSET.h"

#include <limits>

using namespace std;

PointSET::PointSET(): size(0){};

bool PointSET::isEmpty(){
	if(size == 0) return true;
	else return false;
}

void PointSET::insert(Point2D p){
	p_set.insert(p);
	size++;
}

bool PointSET::contains(Point2D p){
	auto itr = p_set.find(p);
	if(itr != p_set.end()) return true;
	else return false;
}

//void PointSET::draw(){}

vector<Point2D>& PointSET::range(RectHV rect){
	vector<Point2D> vec = new vector<Point2D>;
	for(const auto& element : p_set){
		if(rect.contains(element)) vec.push_back(element);
	}
	return vec;
}

Point2D* PointSET::nearest(Point2D p){
	Point2D* n_point = new Point2D();
	double min_dist = numeric_limits<double>::infinity;

	if(p_set.empty) return nullptr;
	else{
		for(const auto& element : p_set){
			double curr_dist = p.distanceSquaredTo(element);
			if(curr_dist < min_dist){
				max_dist = curr_dist;
				n_point = &element;
			}
		}
	}
	return n_point;
}

