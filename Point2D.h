#include <string>

using namespace std;

class Point2D{
public:
	Point2D(double x, double y);
	Point2D();

	double distanceTo(Point2D that);
	double distanceSquaredTo(Point2D that);
	
	bool operator<(const Point2D &rhs);
	
	template <class Object>
	bool equals(Object that){
		if(that == this) return true;
		if(that == NULL) return false;
		if(typeid(that) != typeid(this)) return false;

		if(x == that.x && y == that.y) return true;

		return false;
	};
	
//	void draw();
	String toString();

	double x;
	double y;
};


