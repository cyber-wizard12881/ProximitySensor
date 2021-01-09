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

//The Node of the KD Tree
class KDTREE_API Node {
public:
	//Constructor
	Node(Point* point, BB* boundingBox);
	//Destructor
	~Node();
	//The Leaf Node ... if Null -> Non-Leaf Node ... if Not Null -> Leaf Node
	Point* point;
	//The Non-Leaf Node .. if Null -> Leaf Node ... if Not Null -> Non-Leaf Node
	BB* boundingBox;
	//Pointer to the Left Child Node
	Node* left;
	//Pointer to the Right Child Node
	Node* right;
	//Is the Current Node the Left or the Right Child of its Parent?
	bool isLeftChild;
	//Get the Bounding Box's Region
	Range* GetBounds();
	//Get the Pointer to the Parent of this Node
	Node* parent;
};

//The Bounding Box (Non-Leaf Nodes)
class KDTREE_API BB {
public:
	//Constructor
	BB(int K, int cutDimension, int value, Node* left, Node* right);
	//Destructor
	~BB();
	//Set the Outer Window or Bounds
	void SetOuterRegion(Range* region);
	//Store Pointer to it's Left Child ... This is used in the Actual KD Tree's Traversal!!!
	Node* left;
	//Store Pointer to it's Right Child ... This is used in the Actual KD Tree's Traversal!!!
	Node* right;
	//The Number of Dimensions
	int K;
	//The Cut Dimension ... X or Y? for instance ...
	int cutDimension;
	//The Value of the Cut Dimension!! X=1 or Y=2 for instance ....
	int value;
	//The Bounds associated with the Bounding Box
	deque<int> bounds;
	//The outer region or Window
	Range* outerRegion;	
};
