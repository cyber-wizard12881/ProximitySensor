// ProximitySensor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "KNN.h"
#include "PKNN.h"
#include <vector>
#include "ProximitySensor.h"
#include <chrono>

using namespace std;

void KNNOperations();
void PKNNOperations();

int main()
{
	KNNOperations();
	PKNNOperations();
	return getchar();
}

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
