#pragma once
#include "KNN.h"
#include <ppl.h>
#include <concurrent_vector.h>
#include "KNNP.h"

#ifdef KNN_EXPORTS
#  define KNN_API __declspec(dllexport)
#else
#  define KNN_API __declspec(dllimport)
#endif

using namespace concurrency;
using namespace std;

//Class for the Parallel KNN Range Based Search
class KNN_API PKNN {
public:
	//Constructor
	PKNN(int K, int NN, vector<Point*> points, Range* region, Range* range,int N);
	//Destructor
	~PKNN();
	//Build Pseudo-Parallel KNN list objects (data-partitioned)
	void BuildKNNs();
	//Build the Pseudo Parllel KD Trees .... actually with serial containers (data structures) ... cause of the slowness observed on execution time .....
	void BuildKdTrees();
	//Pseudo Parallel KNN Range Based Search ---> 1. KD Tree Construction using Serial Containers ... 2. Search in Parallel using Parallel Containers
	void PSearch();
	//Actual Pseudo-Parallel Search that calls into the Serial KNN Structures in Parallel 
	void Search(KNN* knn, Node* node, Range* range, concurrent_vector<Node*>* nodes);
	//Collect the Pseudo-Parallel Points Result-Set
	void Points(Node* root, concurrent_vector<Point*>* points);
	//Remove Duplicates from the Result-Set
	void RemoveDuplicatePoints();
	//Number of Processes/Threads to Divide the Points Set .... the Input into batches per se....
	int N;
	//Serial KNN Object
	KNN* knn;
	//List of Serial KNN Objects used by the Pseudo-Parallel Algorithm
	concurrent_vector<KNN*> knns;
	int K;
	//Number of Nearest Neighbors
	int NN;
	//Size of the Points Vector
	int P;
	//Serial Container for Points (Psuedo-Parallel Algorithm)
	vector<Point*> points;
	//Size of the Points Batch Set
	int PP;
	//Region for the Bounds of the KD Tree
	Range* region;
	//Input range of Bounds that we want to locate points within or in .....  
	Range* range;
	//Pseudo-Parallel Container Objects used by PPL -> Parallel Patterns Library
	concurrent_vector<Node*> pNodes;
	concurrent_vector<Point*> pNearestOnes;

	void SetKNNPPoints(concurrent_vector<Point*> points);
	//Build Parallel KNN list objects (data-partitioned)
	void BuildKNNPs();
	//Build Parallel KD Trees
	void BuildPKdTrees();
	//Run the Parallel KNN Search
	void KNNPSearch();
	//Build the Parallel KNN Range Points Result-Set
	void KNNPPoints(Node* root, concurrent_vector<Point*>* points);
	//Get rid of duplicates from the result-set
	void RemoveKNNPDuplicatePoints();
	//Parallel Container Objects (PPL->Parallel Patterns Library) to store relevant info .....
	concurrent_vector<KNNP*> knnps;
	concurrent_vector<Point*> knnpPoints;
	concurrent_vector<Node*> knnpNodes;
	concurrent_vector<Point*> knnpNearestOnes;
};
