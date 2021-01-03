#pragma once
#include "Node.h"
#include "Range.h"

#ifdef KDTREE_EXPORTS
#  define KDTREE_API __declspec(dllexport)
#else
#  define KDTREE_API __declspec(dllimport)
#endif

class KDTREE_API KdTree {
public:
	KdTree();
	KdTree(int K);
	~KdTree();
	Node* Insert(vector<Point*> points, int depth, deque<int> bounds);
	Node* Find(Node* root, Point* point, int depth);
	Point* FindMin(Node* root, int currentDimension, int cutDimension);
	Point* FindMax(Node* root, int currentDimension, int cutDimension);
	void Points(Node* root, vector<Point*>* points);
	void SetRegion(Range* region);
	int K;
	Node* root;
	void Print(Node* root);
	Range* region;
	int min;
	int max;
	Node* maxNode;
	Node* minNode;
};