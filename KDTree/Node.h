#pragma once
#include "Point.h"
#include "Range.h"
#include <deque>

#ifdef KDTREE_EXPORTS
#  define KDTREE_API __declspec(dllexport)
#else
#  define KDTREE_API __declspec(dllimport)
#endif

class KDTREE_API BB;
class KDTREE_API Range;

class KDTREE_API Node {
public:
	Node(Point* point, BB* boundingBox);
	~Node();
	Point* point;
	BB* boundingBox;
	Node* left;
	Node* right;
	bool isLeftChild;
	Range* GetBounds();
	Node* parent;
};

class KDTREE_API BB {
public:
	BB(int K, int cutDimension, int value, Node* left, Node* right);
	~BB();
	void SetOuterRegion(Range* region);
	Node* left;
	Node* right;
	int K;
	int cutDimension;
	int value;
	deque<int> bounds;
	Range* outerRegion;	
};
