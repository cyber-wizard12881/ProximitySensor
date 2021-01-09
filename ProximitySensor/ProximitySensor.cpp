// ProximitySensor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "KNN.h"
#include "PKNN.h"
#include <vector>
#include "ProximitySensor.h"
#include <chrono>

using namespace std;

//The Serial KNN Range Search Algorithm Invoker
void KNNOperations();
//The Pseudo-Parallel KNN Range Search Algorithm Invoker
void PKNNOperations();
//The Parallel KNN Range Search Algorithm Invoker
void PKNNPOperations();

int main()
{
	//1. Call Serial KNN
	KNNOperations();
	//2. Call Pseduo-Parallel KNN
	PKNNOperations();
	//3. Call Parallel KNN
	PKNNPOperations();
	return getchar();
}

//3. Parallel KNN Range Based Search Invoker
void PKNNPOperations()
{
	cout << "-------Starting the Parallel KNNP Range Search Program------------" << endl;
	Node* root = NULL;
	PKdTree* kdTree = new PKdTree(2);
	vector<Point*>* points = new vector<Point*>();
	concurrent_vector<Point*>* knnpPoints = new concurrent_vector<Point*>();
	knnpPoints->push_back(new Point(2, 3, 6));
	knnpPoints->push_back(new Point(2, 17, 15));
	knnpPoints->push_back(new Point(2, 13, 15));
	knnpPoints->push_back(new Point(2, 6, 12));
	knnpPoints->push_back(new Point(2, 9, 1));
	knnpPoints->push_back(new Point(2, 2, 7));
	knnpPoints->push_back(new Point(2, 10, 19));

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;

	vector<int> regionFrom, regionTo;
	regionFrom.push_back(0);
	regionFrom.push_back(0);
	regionTo.push_back(21);
	regionTo.push_back(21);

	vector<int> rangeFrom, rangeTo;
	rangeFrom.push_back(10);
	rangeFrom.push_back(13);
	rangeTo.push_back(18);
	rangeTo.push_back(16);
	Range* range = new Range(2, rangeFrom, rangeTo);

	Range* region = new Range(2, regionFrom, regionTo);
	start = std::chrono::steady_clock::now();
	PKNN* pKNN = new PKNN(2, 2, *points, region, range, 4);
	pKNN->SetKNNPPoints(*knnpPoints);
	end = std::chrono::steady_clock::now();
	cout << "Time to Set the KNNPPoints is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	start = std::chrono::steady_clock::now();
	pKNN->BuildKNNPs();
	end = std::chrono::steady_clock::now();
	cout << "Time to build the Parallel KNNPs is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	start = std::chrono::steady_clock::now();
	pKNN->BuildPKdTrees();
	end = std::chrono::steady_clock::now();
	cout << "Time to build the Parallel PKdTrees is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	start = std::chrono::steady_clock::now();
	pKNN->KNNPSearch();
	pKNN->RemoveKNNPDuplicatePoints();
	end = std::chrono::steady_clock::now();
	cout << "Time to search the Range using Parallel KNNP (KdTree) is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	cout << "-------Printing Results of the Parallel KNNP Range Search------------" << endl;
	range->Plot();
	cout << "Points in the Range are: " << endl;
	for (int idx = 0; idx < pKNN->knnpNearestOnes.size(); idx++) {
		pKNN->knnpNearestOnes[idx]->Plot();
	}
	cout << "-------Ending the Parallel KNNP Range Search Program------------" << endl;
}

//2. Pseudo-Parallel KNN Range Based Search Invoker
void PKNNOperations()
{
	cout << "-------Starting the Parallel KNN Range Search Program------------" << endl;
	Node* root = NULL;
	KdTree* kdTree = new KdTree(2);
	vector<Point*>* points = new vector<Point*>();
	points->push_back(new Point(2, 3, 6));
	points->push_back(new Point(2, 17, 15));
	points->push_back(new Point(2, 13, 15));
	points->push_back(new Point(2, 6, 12));
	points->push_back(new Point(2, 9, 1));
	points->push_back(new Point(2, 2, 7));
	points->push_back(new Point(2, 10, 19));

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;

	vector<int> regionFrom, regionTo;
	regionFrom.push_back(0);
	regionFrom.push_back(0);
	regionTo.push_back(21);
	regionTo.push_back(21);

	vector<int> rangeFrom, rangeTo;
	rangeFrom.push_back(10);
	rangeFrom.push_back(13);
	rangeTo.push_back(18);
	rangeTo.push_back(16);
	Range* range = new Range(2, rangeFrom, rangeTo);

	Range* region = new Range(2, regionFrom, regionTo);
	start = std::chrono::steady_clock::now();
	PKNN* pKNN = new PKNN(2, 2, *points, region, range, 4);
	pKNN->BuildKNNs();
	end = std::chrono::steady_clock::now();
	cout << "Time to build the Parallel KNNs is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	start = std::chrono::steady_clock::now();
	pKNN->BuildKdTrees();
	end = std::chrono::steady_clock::now();
	cout << "Time to build the Parallel KdTrees is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	start = std::chrono::steady_clock::now();
	pKNN->PSearch();
	pKNN->RemoveDuplicatePoints();
	end = std::chrono::steady_clock::now();
	cout << "Time to search the Range using Parallel KNN (KdTree) is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	cout << "-------Printing Results of the Parallel KNN Range Search------------" << endl;
	range->Plot();
	cout << "Points in the Range are: " << endl;
	for (int idx = 0; idx < pKNN->pNearestOnes.size(); idx++) {
		pKNN->pNearestOnes[idx]->Plot();
	}
	cout << "-------Ending the Parallel KNN Range Search Program------------" << endl;
}

//1. Serial KNN Range Based Search Invoker
void KNNOperations()
{
	cout << "-------Starting the KNN Range Search Program------------" << endl;
	Node* root = NULL;
	KdTree* kdTree = new KdTree(2);
	vector<Point*>* points = new vector<Point*>();
	points->push_back(new Point(2, 3, 6));
	points->push_back(new Point(2, 17, 15));
	points->push_back(new Point(2, 13, 15));
	points->push_back(new Point(2, 6, 12));
	points->push_back(new Point(2, 9, 1));
	points->push_back(new Point(2, 2, 7));
	points->push_back(new Point(2, 10, 19));
	
	std::chrono::steady_clock::time_point start; 
	std::chrono::steady_clock::time_point end;

	start = std::chrono::steady_clock::now();
	KNN* kNN = new KNN(2, 2, *points);
	vector<int> regionFrom, regionTo;
	regionFrom.push_back(0);
	regionFrom.push_back(0);
	regionTo.push_back(21);
	regionTo.push_back(21);
	Range* region = new Range(2, regionFrom, regionTo);
	kNN->KDTree->SetRegion(region);
	kNN->BuildKdTree();
	end = std::chrono::steady_clock::now();
	cout << "Time to build the KdTree is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	vector<int> rangeFrom, rangeTo;
	rangeFrom.push_back(10);
	rangeFrom.push_back(13);
	rangeTo.push_back(18);
	rangeTo.push_back(16);
	Range* range = new Range(2, rangeFrom, rangeTo);
	vector<Node*> nodes;
	vector<Point*> nearestOnes;

	start = std::chrono::steady_clock::now();
	kNN->Search(kNN->KDTree->root, range, &nodes);
	for (int idx = 0; idx < nodes.size(); idx++) {
		kNN->KDTree->Points(nodes[idx], &nearestOnes);
	}
	end = std::chrono::steady_clock::now();
	cout << "Time to search the Range using KNN (KdTree) is " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds." << endl;

	cout << "-------Printing Results of the KNN Range Search------------" << endl;
	range->Plot();
	cout << "Points in the Range are: " << endl;
	for (int idx = 0; idx < nearestOnes.size(); idx++) {
		nearestOnes[idx]->Plot();
	}
	cout << "-------Ending the KNN Range Search Program------------" << endl;
}
