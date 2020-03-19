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

vector<Point2D> range(RectHV rect){
	vector<Point2D> vec = new vector<Point2D>;
	stack<Point2D*> divider;

	size_t height = 0;
	node_t* now = root;

	while(now != nullptr){
		if(rect.contains(now)){	// needs to check both subtree
			divider.push(now);	// save the point which should be search for another subtree.
			vec.push_back(now);
			now = now->lb;
		}
		else{
			if(height % 2 == 0){
				if(rect.xmax < now.x){	// rect is located to left.
					now = now->lb;
				}
				else{
					now = now->rt;
				}
			}
			else{
				if(rect.ymax < now.y){	// rect is located to bottom.
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
			if(rect.contains(now)){	// needs to check both subtree
				divider.push(now);	// save the point which should be search for another subtree.
				vec.push_back(now);
				now = now->lb;
			}
			else{
				if(height % 2 == 0){
					if(rect.xmax < now.x){	// rect is located to left.
						now = now->lb;
					}
					else{
						now = now->rt;
					}
				}
				else{
					if(rect.ymax < now.y){	// rect is located to bottom.
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


