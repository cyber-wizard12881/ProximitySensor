#pragma once
#include "KNN.h"
#include <ppl.h>
#include <concurrent_vector.h>

#ifdef KNN_EXPORTS
#  define KNN_API __declspec(dllexport)
#else
#  define KNN_API __declspec(dllimport)
#endif

using namespace concurrency;
using namespace std;

class KNN_API PKNN {
public:
	PKNN(int K, int NN, vector<Point*> points, Range* region, Range* range,int N);
	~PKNN();
	void BuildKNNs();
	void BuildKdTrees();
	void PSearch();
	void Search(KNN* knn, Node* node, Range* range, concurrent_vector<Node*>* nodes);
	void Points(Node* root, concurrent_vector<Point*>* points);
	void RemoveDuplicatePoints();
	int N;
	KNN* knn;
	concurrent_vector<KNN*> knns;
	int K;
	int NN;
	int P;
	vector<Point*> points;
	int PP;
	Range* region;
	Range* range;
	concurrent_vector<Node*> pNodes;
	concurrent_vector<Point*> pNearestOnes;
};
