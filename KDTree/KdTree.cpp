#include "pch.h"
#include "KdTree.h"
#include "Sorter.h"

//Default Constructor for the Serial KD Tree
KdTree::KdTree()
{
	this->K = 0;
	this->root = NULL;
	this->min = INT_MAX;
	this->max = INT_MIN;
	this->maxNode = NULL;
	this->minNode = NULL;
}

//Constructor for the K Dimensions of the KD Tree
KdTree::KdTree(int K)
{
	this->K = K;
	this->root = NULL;
	this->min = INT_MAX;
	this->max = INT_MIN;
	this->maxNode = NULL;
	this->minNode = NULL;
}

//The Serial KD Tree Destructor
KdTree::~KdTree()
{
	this->K = 0;
	delete this->root;
	this->root = NULL;
	this->min = 0;
	this->max = 0;
	delete this->maxNode;
	this->maxNode = NULL;
	delete this->minNode;
	this->minNode = NULL;
}

//Inserting a Node into the Serial KD Tree
Node* KdTree::Insert(vector<Point*> points, int depth, deque<int> bounds)
{
	unsigned int currentDimension = depth % this->K;

	if (points.size() == size_t(1)) {
		points[0]->cutDimension = currentDimension;
		return new Node(points[0], NULL);
	}

	vector<Point*> sortedOnes = Sorter::Sort(points, currentDimension);
	Point* middleOne = Sorter::FindMedian(sortedOnes);
	pair<vector<Point*>, vector<Point*>> sortedPairs = Sorter::Split(sortedOnes, middleOne, currentDimension);

	BB* bb = new BB(this->K, currentDimension, middleOne->datum[currentDimension], NULL, NULL);
	Node* node = new Node(NULL, bb);
	bounds.push_back(middleOne->datum[currentDimension]);
	node->boundingBox->bounds = bounds;
	node->boundingBox->SetOuterRegion(this->region);
	node->boundingBox->left = this->Insert(sortedPairs.first, depth + 1, bounds);
	node->boundingBox->left->isLeftChild = true;
	node->boundingBox->left->parent = node;
	node->boundingBox->right = this->Insert(sortedPairs.second, depth + 1, bounds);
	node->boundingBox->right->isLeftChild = false;
	node->boundingBox->right->parent = node;
	return node;
}

//Find a Node at the specified root in the Serial KD Tree
Node* KdTree::Find(Node* root, Point* point, int depth)
{
	if (root == NULL)
		return NULL;
	if (root->point != NULL) {
		if (*root->point == *point)
			return root;
		else
			return NULL;
	}
	unsigned int currentDimension = depth % this->K;
	if (root->boundingBox != NULL) {
		if (currentDimension == root->boundingBox->cutDimension) {
			if (point->datum[currentDimension] <= root->boundingBox->value)
				this->Find(root->boundingBox->left, point, depth + 1);
			else
				this->Find(root->boundingBox->right, point, depth + 1);
		}
		else {
			if (point->datum[root->boundingBox->cutDimension] <= root->boundingBox->value)
				this->Find(root->boundingBox->left, point, depth + 1);
			else
				this->Find(root->boundingBox->right, point, depth + 1);
		}
	}
}

//Find the Min Node rooted at the root in the Serial KD Tree
Point* KdTree::FindMin(Node* root, int currentDimension, int cutDimension)
{
	if (root == NULL) {
		return NULL;
	}
	if (root->boundingBox == NULL && root->point != NULL) {
		return new Point(root->point);
	}
	if (currentDimension == cutDimension) {
		if (root->boundingBox == NULL && root->point != NULL) {
			return new Point(root->point);
		}
		else if (root != NULL && root->boundingBox != NULL) {
			return FindMin(root->boundingBox->left, currentDimension, (cutDimension + 1) % this->K);
		}
	}
	else if (root != NULL && root->boundingBox != NULL) {
		return min(FindMin(root->boundingBox->left, currentDimension, (cutDimension + 1) % this->K)
			, FindMin(root->boundingBox->right, currentDimension, (cutDimension + 1) % this->K),
			root->point);
	}
}

//Find the Max Node rooted at the root in the Serial KD Tree
Point* KdTree::FindMax(Node* root, int currentDimension, int cutDimension)
{
	if (root == NULL) {
		return NULL;
	}
	if (root->boundingBox == NULL && root->point != NULL) {
		return new Point(root->point);
	}
	if (currentDimension == cutDimension) {
		if (root->boundingBox == NULL && root->point != NULL) {
			return new Point(root->point);
		}
		else if (root != NULL && root->boundingBox != NULL) {
			return FindMax(root->boundingBox->right, currentDimension, (cutDimension + 1) % this->K);
		}
	}
	else if (root != NULL && root->boundingBox != NULL) {
		return max(FindMax(root->boundingBox->right, currentDimension, (cutDimension + 1) % this->K)
			, FindMax(root->boundingBox->left, currentDimension, (cutDimension + 1) % this->K),
			root->point);
	}
}

//Collect the Points rooted at the root in the Serial KD Tree
void KdTree::Points(Node* root, vector<Point*>* points)
{
	if (root == NULL)
		return;
	if (root->boundingBox != NULL)
		Points(root->boundingBox->left, points);
	if (root->point != NULL)
		points->push_back(root->point);
	if (root->boundingBox != NULL)
		Points(root->boundingBox->right, points);
}

//Set the Outer Region or the window of the Serial KD Tree
void KdTree::SetRegion(Range* region)
{
	this->region = region;
}

//Pretty Print Serial KD Tree's Contents in In-Order Traversal onto the Console
void KdTree::Print(Node* root)
{
	if (root == NULL)
		return;
	if (root->boundingBox != NULL)
		Print(root->boundingBox->left);
	if (root->point != NULL)
		root->point->Plot();
	if (root->boundingBox != NULL)
		Print(root->boundingBox->right);
}
