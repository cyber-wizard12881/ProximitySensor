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

//The Parallel KD Tree Structure ... [Uses Parallel Containers Only]
class KDTREE_API PKdTree {
public:
	//Default Constructor
	PKdTree();
	//Constructor
	PKdTree(int K);
	//Destructor
	~PKdTree();
	//Insert a Node into the KD Tree
	Node* Insert(concurrent_vector<Point*> points, int depth, deque<int> bounds);
	//Find a Node in a KD Tree
	Node* Find(Node* root, Point* point, int depth);
	//Find the Min Node at a given root?
	Point* FindMin(Node* root, int currentDimension, int cutDimension);
	//Find the Max Node at a given root?
	Point* FindMax(Node* root, int currentDimension, int cutDimension);
	//Collect the Points Result-Set
	void Points(Node* root, concurrent_vector<Point*>* points);
	//Set the Outer Bounds for the KD Tree ... the window
	void SetRegion(Range* region);
	//The Number of Dimensions
	int K;
	//The Root of the KD Tree
	Node* root;
	//Pretty Print the KD Tree using In-Order Traversal
	void Print(Node* root);
	//the Region or the Outer Bounds
	Range* region;
	//Min Value for Find Min Algo.
	int min;
	//Max Value for Find Max Algo.
	int max;
	//The Max Node...
	Node* maxNode;
	//The Min  Node...
	Node* minNode;
};