#include "pch.h"
#include "Node.h"
#include <map>

Node::Node(Point* point, BB* boundingBox)
{
	this->point = point;
	this->boundingBox = boundingBox;
	this->left = NULL;
	this->right = NULL;
}

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

BB::BB(int K, int cutDimension, int value, Node* left, Node* right)
{
	this->K = K;
	this->cutDimension = cutDimension;
	this->value = value;
	this->left = left;
	this->right = right;
}

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

void BB::SetOuterRegion(Range* region)
{
	this->outerRegion = region;
}

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
