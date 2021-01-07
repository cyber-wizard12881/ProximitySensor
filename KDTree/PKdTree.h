#pragma once
#include "Node.h"
#include "Range.h"
#include <concurrent_vector.h>

#ifdef KDTREE_EXPORTS
#  define KDTREE_API __declspec(dllexport)
#else
#  define KDTREE_API __declspec(dllimport)
#endif

using namespace concurrency;
using namespace std;

class KDTREE_API PKdTree {
public:
	PKdTree();
	PKdTree(int K);
	~PKdTree();
	Node* Insert(concurrent_vector<Point*> points, int depth, deque<int> bounds);
	Node* Find(Node* root, Point* point, int depth);
	Point* FindMin(Node* root, int currentDimension, int cutDimension);
	Point* FindMax(Node* root, int currentDimension, int cutDimension);
	void Points(Node* root, concurrent_vector<Point*>* points);
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