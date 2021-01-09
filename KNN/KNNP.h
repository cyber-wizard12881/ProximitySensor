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

//Parallel KNN Range based Search Alogrithm .... [Strictly Uses Parallel Container Objects only] ... hence very fast execution times observed .... 
class KNN_API KNNP
{
public:
	//Constructor of the Parallel KNN Range Based Search Algorithm
	KNNP(int K, int NN, concurrent_vector<Point*> points);
	//Build a KD Tree in Parallel
	Node* BuildPKdTree();
	//Parallel KNN Range Based Search
	void Search(Node* node, Range* range, concurrent_vector<Node*>* nodes);
	//Default Constructor
	KNNP();
	//The Destructor
	~KNNP();
	//The Parallel KD Tree Structure (Backing Store)
	PKdTree* KDTree;
	//The root of the Parallel KD Tree
	Node* root;
	//Parallel Containers for the Parallel Search Algorithm
	concurrent_vector<Point*> points;
	concurrent_vector<Point*> nearestPoints;
	//Input Region or outer bounds for the KD Tree
	Range* region;
	//The Number of Dimensions
	int K;
	//The Number of Nearest Neighbors
	int NN;
};