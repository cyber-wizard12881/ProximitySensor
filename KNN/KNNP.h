#pragma once
#include "PKdTree.h"
#include "Node.h"
#include <vector>
#include <queue>
#include <string>
#include "Range.h"
#include "Utility.h"
#include <concurrent_vector.h>

#ifdef KNN_EXPORTS
#  define KNN_API __declspec(dllexport)
#else
#  define KNN_API __declspec(dllimport)
#endif

using namespace concurrency;
using namespace std;

class KNN_API KNNP
{
public:
	KNNP(int K, int NN, concurrent_vector<Point*> points);
	Node* BuildPKdTree();
	void Search(Node* node, Range* range, concurrent_vector<Node*>* nodes);
	KNNP();
	~KNNP();
	PKdTree* KDTree;
	Node* root;
	concurrent_vector<Point*> points;
	concurrent_vector<Point*> nearestPoints;
	Range* region;
	int K;
	int NN;
};