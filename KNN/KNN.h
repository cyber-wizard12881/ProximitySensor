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

class KNN_API KNN
{
public:
	KNN(int K, int NN, vector<Point*> points);
	Node* BuildKdTree();
	void Search(Node* node, Range* range, vector<Node*>* nodes);
	KNN();
	~KNN();
	KdTree* KDTree;
	Node* root;
	vector<Point*> points;
	vector<Point*> nearestPoints;
	Range* region;
	int K;
	int NN;
};