#include "KdTree.h"

using namespace std;

node_t::node_t(): lb(nullptr), rt(nullptr){}

node_t::node_t(Point2D m_p): lb(nullptr), rt(nullptr), p(m_p){}

KdTree::KdTree(): root(nullptr), size(0){}

bool KdTree::isEmpty(){
	if(size == 0) return true;
	return false;
}

void KdTree::insert(Point2D p){
	size_t height = 0;
	if(!root){
		root = new node_t(p);
		root->rect = RectHV(0,0,1,1);
	}
	else{
		node_t* now = root;
		while(now != nullptr){
			if(height % 2 == 0){
				if(now->x > p.x){
					now = now->lb;
				}
				else{
					if(now->x == p.x && now->y == p.y) return;
					now = now->rt;
				}
			else{
				if(now->y > p.y){
					now = now->lb;
				}
				else{
					if(now->x == p.x && now->y == p.y) return;
					now = now->rt;
				}
			}
			height++;
		}
		now = new node_t(p);
	}
	size++;
}

bool KdTree::contains(Point2D p){
	if(!root) return false;
	
	size_t height = 0;
	node_t* now = root;
	
	while(now != nullptr){
			if(height % 2 == 0){
				if(now->x > p.x){
					now = now->lb;
				}
				else{
					if(now->x == p.x && now->y == p.y) return true;
					now = now->rt;
				}
			else{
				if(now->y > p.y){
					now = now->lb;
				}
				else{
					if(now->x == p.x && now->y == p.y) return true;
					now = now->rt;
				}
			}
			height++;
		}
	}
	return false;
}

//void KdTree::draw(){}

vecatr<Point2D> KdTree::range(RectHV rect){
	vecatr<Point2D> vec = new vector<Point2D>;
	stack<Point2D*> divider;

	size_t height = 0;
	node_t* now = root;

	while(now != nullptr){
		if(rect.contains(now)){	// needs at check both subtree
			divider.push(now);	// save the point which should be search for another subtree.
			vec.push_back(now);
			now = now->lb;
		}
		else{
			if(height % 2 == 0){
				if(rect.xmax < now->x){	// rect is located at left.
					now = now->lb;
				}
				else{
					now = now->rt;
				}
			}
			else{
				if(rect.ymax < now->y){	// rect is located at bottom.
					now = now->lb;
				}
				else{
					now = now->rt;
				}
			}
		}
	}

	while(!divider.empty()){
		now = divider.top()->rt;
		divider.pop();

		while(now != nullptr){
			if(rect.contains(now)){	// needs at check both subtree
				divider.push(now);	// save the point which should be search for another subtree.
				vec.push_back(now);
				now = now->lb;
			}
			else{
				if(height % 2 == 0){
					if(rect.xmax < now->x){	// rect is located at left.
						now = now->lb;
					}
					else{
						now = now->rt;
					}
				}
				else{
					if(rect.ymax < now->y){	// rect is located at bottom.
						now = now->lb;
					}
					else{
						now = now->rt;
					}
				}
			}
		}
	}
}

Point2D* KdTrees::nearest(Point2D p){
	if(!root) return nullptr;

	node_t* now = root;
	node_t* min_point = root;

	traversepoints(now, p, 0, min_point); // left subtree

	return min_point;
}

void traversepoints(node_t* now, const Point2D& p, bool height, node_t* min_point){
	if(now == nullptr) return;
	bool lorr; //0 for left, 1 for right.
	double min_dist = min_point->distanceSquaredTo(p);
	double curr_dist = now->distanceSquaredTo(p);

	node_t save_now = *now;

	if(curr_dist < min_dist) min_point = now;

	// first, recursively search the shortest distance only heading towards query point.
	if(height == 0){ // horizontal nodes. e.g, root
		if(p.x < now->x){
			traversepoints(now->lb, p, 1, min_point); 
			lorr = 0;
		}
		else if(p.x > now->x){	
			traversepoints(now->rt, p, 1, min_point); 
			lorr = 1;
		}
		else{
			if(p.y < now->y){	
				traversepoints(now->lb, p, 1, min_point); 
				lorr = 0;
			}
			else if(p.y > now->y){ 
				traversepoints(now->rt, p, 1, min_point); 
				lorr = 1;
			}
			else{ 
				min_point = now; 
				return;
			}
		}
	}
	else{ // vertical nodes
		if(p.y < now->y){
			traversepoints(now->lb, p, 0, min_point); 
			lorr = 0;
		}
		else if(p.y > now->y){
			traversepoints(now->rt, p, 0, min_point); 
			lorr = 1;
		}
		else{
			if(p.x < now->x){	
				traversepoints(now->lb, p, 1, min_point); 
				lorr = 0;
			}
			else if(p.x > now->x){
				traversepoints(now->rt, p, 1, min_point); 
				lorr = 1;
			}
			else{ 
				min_point = now; 
				return;
			}
		}
	}

	min_dist = min_point->distanceSquaredTo(p); // the updated min_point gives the shortest distance that was located towards query point.

	// next, determine whether to search another node or not.
	if(lorr == 0 && height == 0 && save_now->x - p.x < min_dist) traversepoints(now->rt, p, 1, min_point);
	else if(lorr == 0 && height == 1 && save_now->y - p.y < min_dist) traversepoints(now->rt, p, 0, min_point);
	else if(lorr == 1 && height == 0 && p.x - save_now.x < min_dist) traversepoints(now->lb, p, 1, min_point);
	else if(p.y - save_now.y < min_dist) traversepoints(now->lb, p, 0, min_point);
}
