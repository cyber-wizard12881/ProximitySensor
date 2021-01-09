#pragma once
#include "KdTree.h"
#include "Node.h"
#include <vector>
#include <queue>
#include <string>
#include "Range.h"
#include "Utility.h"

#ifdef KNN_EXPORTS
#  define KNN_API __declspec(dllexport)
#else
#  define KNN_API __declspec(dllimport)
#endif

//Serial KNN Range Based Search Algorithm
class KNN_API KNN
{
public:
	//Constructor
	KNN(int K, int NN, vector<Point*> points);
	//Build Serial KD Tree
	Node* BuildKdTree();
	//Perform a Serial KNN Range Based Search
	void Search(Node* node, Range* range, vector<Node*>* nodes);
	//Default Constructor
	KNN();
	//The Destructor
	~KNN();
	//The Serial KD Tree
	KdTree* KDTree;
	//Root of the Serial KD Tree
	Node* root;
	//Serial Containers for the Serial KNN Range Based Search 
	vector<Point*> points;
	vector<Point*> nearestPoints;
	//Outer Bounds or Region to consider for the KD Tree
	Range* region;
	//The Number of Dimensions
	int K;
	//The Number of Nearest Neighbors
	int NN;
};