#include "pch.h"
#include "KNNP.h"
#include "Utility.h"

//Parallel KNN Range Based Search Algorithm Constructor
KNNP::KNNP(int K, int NN, concurrent_vector<Point*> points)
{
	this->K = K;
	this->NN = NN;
	this->points = points;
	this->KDTree = new PKdTree(this->K);
}

//Build a Parallel KD Tree
Node* KNNP::BuildPKdTree()
{
	this->root = NULL;
	deque<int> bounds;
	this->root = this->KDTree->Insert(this->points, 0, bounds);
	this->KDTree->root = this->root;
	return root;
}

//Run a Parallel KNN Range Based Search
void KNNP::Search(Node* node, Range* range, concurrent_vector<Node*>* nodes)
{
	if (node != NULL && node->boundingBox == NULL && node->point != NULL)
	{
		if (Utility::Contains(range, node->point)) {
			this->nearestPoints.push_back(node->point);
			nodes->push_back(node);
		}
	}
	else {
		if (node != NULL && node->boundingBox != NULL && Utility::Contains(range, node->boundingBox->left->GetBounds())) {
			nodes->push_back(node->boundingBox->left);
		}
		else {
			if (node != NULL && node->boundingBox != NULL && Utility::Intersects(range, node->boundingBox->left->GetBounds())) {
				Search(node->boundingBox->left, range, nodes);
			}
		}
		if (node != NULL && node->boundingBox != NULL && Utility::Contains(range, node->boundingBox->right->GetBounds())) {
			nodes->push_back(node->boundingBox->right);
		}
		else {
			if (node != NULL && node->boundingBox != NULL && Utility::Intersects(range, node->boundingBox->right->GetBounds())) {
				Search(node->boundingBox->right, range, nodes);
			}
		}
		return;
	}
}

//Parallel KNN Range Based Search Algorithm Default Constructor
KNNP::KNNP()
{
	this->K = 0;
	this->NN = 0;
	this->points.clear();
	this->KDTree = new PKdTree(this->K);
	this->root = NULL;
}

//Parallel KNN Range Based Search Algorithm Destructor
KNNP::~KNNP()
{
	this->K = 0;
	this->NN = 0;
	this->points.clear();
	this->points.shrink_to_fit();
	delete this->KDTree;
	this->KDTree = NULL;
	delete this->root;
	this->root = NULL;
}