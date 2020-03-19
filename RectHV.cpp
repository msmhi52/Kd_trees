#include "RectHV.h"

using namespace std;

RectHV::RectHV(double xmin, double ymin, double xmax, double ymax){
		if(xmin > xmax || ymin > ymax) throw invalid_argument("Minimum coordinates cannot exceed maximum coordinates!!");

		this->xmin = xmin;
		this->ymin = ymin;
		this->xmax = xmax;
		this->ymax = ymax;
	}

bool RectHV::contains(Point2D p){
	if(p.x < xmin || p.y < ymin || p.x > xmax || p.y > ymax) return false;
	return true;
}

bool RectHV::intersects(RectHV that){
	if(xmin > that.xmax || xmax < that.xmin || ymin > that.ymax || ymax < that.ymin) return false;
	return true;
}

double RectHV::distanceTo(Point2D p){
	if(contains(p)) return 0;
	
	if(p.x < xmin){
		if(p.y < ymin) return p.distanceTo(Point2D(xmin, ymin));
		else if(p.y > ymax) return p.distanceTo(Point2D(xmin, ymax));
		else return p.distanceTo(Point2D(xmin, p.y));
	}
	else if(p.x > xmax){
		if(p.y < ymin) return p.distanceTo(Point2D(xmax, ymin));
		else if(p.y > ymax) return p.distanceTo(Point2D(xmax, ymax));
		else return p.distanceTo(Point2D(xmax, p.y));
	}
	else{
		if(p.y < ymin) return p.distanceTo(Point2D(p.x, ymin));
		else(p.y > ymax) return p.distanceTo(Point2D(p.x, ymax));
	}
}

double RectHV::distanceSquaredTo(Point2D p){
	if(contains(p)) return 0;
	
	if(p.x < xmin){
		if(p.y < ymin) return p.distanceSquaredTo(Point2D(xmin, ymin));
		else if(p.y > ymax) return p.distanceSquaredTTo(Point2D(xmin, ymax));
		else return p.distanceSquaredTo(Point2D(xmin, p.y));
	}
	else if(p.x > xmax){
		if(p.y < ymin) return p.distanceSquaredTo(Point2D(xmax, ymin));
		else if(p.y > ymax) return p.distanceSquaredTo(Point2D(xmax, ymax));
		else return p.distanceSquaredTo(Point2D(xmax, p.y));
	}
	else{
		if(p.y < ymin) return p.distanceSquaredTo(Point2D(p.x, ymin));
		else(p.y > ymax) return p.distanceSquaredTo(Point2D(p.x, ymax));
	}
}

//void RectHV::draw(){}

string RectHV::tostring(){
	cout << "[" << xmin << ", " << xmax << "] x [" << ymin << ", " << ymax << "]\n";
}
