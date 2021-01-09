#include "pch.h"
#include "Node.h"
#include <map>

//Create a Node as a Point->Leaf or Bounding Box->Non-Leaf One?
Node::Node(Point* point, BB* boundingBox)
{
	this->point = point;
	this->boundingBox = boundingBox;
	this->left = NULL;
	this->right = NULL;
}

//Destructor of the Node
Node::~Node()
{
	delete& this->point;
	this->point = NULL;
	delete& this->left;
	this->left = NULL;
	delete& this->right;
	this->right = NULL;
	delete& this->boundingBox;
	this->boundingBox = NULL;
}

//Create a Bounding Box ... a Non-Leaf Node!
BB::BB(int K, int cutDimension, int value, Node* left, Node* right)
{
	this->K = K;
	this->cutDimension = cutDimension;
	this->value = value;
	this->left = left;
	this->right = right;
}

//Destructor of the Bounding Box
BB::~BB()
{
	this->K = 0;
	this->cutDimension = 0;
	this->value = 0;
	delete this->left;
	this->left = NULL;
	delete this->right;
	this->right = NULL;
}

//Set Outer Region or Window of the Bounding Box
void BB::SetOuterRegion(Range* region)
{
	this->outerRegion = region;
}

//Get the Bounds bounded by the Bounding Box!!! 
//The Most Important & Critical Part of the KNN Search & the KD Tree
Range* Node::GetBounds()
{
	if (this->boundingBox == NULL && this->point != NULL) {
		vector<int> pointFrom;
		vector<int> pointTo;
		for (int idx = 0; idx < this->point->dimensions; idx++) {
			pointFrom.push_back(this->point->datum[idx]);
			pointTo.push_back(this->point->datum[idx]);
		}
		return new Range(this->point->dimensions, pointFrom, pointTo);
	}
	if (boundingBox != NULL) {
		if (this->boundingBox->bounds.size() == size_t(1)) {
			return this->boundingBox->outerRegion;
		}
		int boundsSize = this->boundingBox->bounds.size();
		int totalDim = 0;
		map<int, int> from;
		map<int, int> to;

		for (int idx = 0; idx < this->boundingBox->K; idx++) {
			from.insert(pair<int, int>(idx, this->boundingBox->outerRegion->from[idx]));
			to.insert(pair<int, int>(idx, this->boundingBox->outerRegion->to[idx]));
		}

		int currDim = boundsSize - 1;
		Node* currNode = this;
		while (totalDim != this->boundingBox->K) {
			int prevDim = currDim - this->boundingBox->K;
			if (prevDim >= 0) {
				int currValueInCurrDimension = this->boundingBox->bounds[currDim];
				int prevValueInCurrDimension = this->boundingBox->bounds[prevDim];
				if (currValueInCurrDimension >= prevValueInCurrDimension) {
					from[currDim % this->boundingBox->K] = prevValueInCurrDimension;
				}
				else {
					to[currDim % this->boundingBox->K] = prevValueInCurrDimension;
				}
				totalDim++;
				while (totalDim != this->boundingBox->K) {
					if (currNode->isLeftChild) {
						to[(currDim - 1) % this->boundingBox->K] = this->parent->boundingBox->value;
					}
					else {
						from[(currDim - 1) % this->boundingBox->K] = this->parent->boundingBox->value;
					}
					currNode = currNode->parent;
					totalDim++;
				}
			}
			else {
				while (totalDim != this->boundingBox->K) {
					if (this->isLeftChild) {
						to[(currDim - 1) % this->boundingBox->K] = this->parent->boundingBox->value;
					}
					else {
						from[(currDim - 1) % this->boundingBox->K] = this->parent->boundingBox->value;
					}
					currNode = currNode->parent;
					totalDim++;
				}
			}
		}

		vector<int> tempFrom;
		vector<int> tempTo;
		for (int idx = 0; idx < this->boundingBox->K; idx++) {
			tempFrom.push_back(from[idx]);
			tempTo.push_back(to[idx]);
		}

		return new Range(this->boundingBox->K, tempFrom, tempTo);
	}
	return NULL;
}
