#pragma once
#include "Node.h"
#include "Range.h"

#ifdef KDTREE_EXPORTS
#  define KDTREE_API __declspec(dllexport)
#else
#  define KDTREE_API __declspec(dllimport)
#endif

//The Serial KD Tree
class KDTREE_API KdTree {
public:
	//Default Constructor
	KdTree();
	//Constructor
	KdTree(int K);
	//Destructor
	~KdTree();
	//Insert a Node in the KD Tree
	Node* Insert(vector<Point*> points, int depth, deque<int> bounds);
	//Find a Node in the KD Tree?
	Node* Find(Node* root, Point* point, int depth);
	//Find Min Node at the specified root in the KD Tree?
	Point* FindMin(Node* root, int currentDimension, int cutDimension);
	//Find the Max Node at the specified root in the KD Tree?
	Point* FindMax(Node* root, int currentDimension, int cutDimension);
	//Collect the Points in the Result-Set
	void Points(Node* root, vector<Point*>* points);
	//Set the Outer Region or the window
	void SetRegion(Range* region);
	//Number of Dimensions?
	int K;
	//The Root of the KD Tree?
	Node* root;
	//Pretty Print the KD Tree's Contents using In-Order Traversal onto the console
	void Print(Node* root);
	//The Outer Region or the window
	Range* region;
	//Min Value in Find Min algo.
	int min;
	//Max Value in Find Max algo.
	int max;
	//The Max Node found using Find Max?
	Node* maxNode;
	//The Min Node found using Find Min?
	Node* minNode;
};