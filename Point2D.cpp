#include "Point2D"

#include <SDL2/SDL.h>

#include <cmath>
#include <limits>
#include <set>

using namespace std;

Point2D::Point2D(double x, double y){
	if(isnan(x) || isnan(y) || isinf(x) || isinf(y) ) throw invalid_argument("Input value cannot be nan or inf!!");
	this->x = x;
	this->y = y;
}

double Point2D::distance2D(Point2D that){
	return sqrt((x - that.x) * (x - that.x) + (y - that.y) * (y - that.y));
}

double Point2D::distanceSquaredTo(Point2D that){
	return (x - that.x) * (x - that.x) + (y - that.y) * (y - that.y);
}

bool Point2D::operator<(const Point2D &rhs){
	if(y == rhs.y){
		return x < rhs.x;
	}
	return y < rhs.y;
}

//void Point2D::draw(){}

string Point2D::toString(){
	cout << "(" << x << ", " << ")\n";
}

