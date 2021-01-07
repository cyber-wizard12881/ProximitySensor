#include "pch.h"
#include "PKNN.h"
#include <set>

using namespace concurrency;
using namespace std;

PKNN::PKNN(int K, int NN, vector<Point*> points, Range* region, Range* range, int N)
{
	this->K = K;
	this->NN;
	this->points = points;
	this->region = region;
	this->range = range;
	this->P = points.size();
	this->N = N;
	this->PP = this->P / this->N;
}

PKNN::~PKNN()
{
	this->K = 0;
	this->NN = 0;
	this->N = 0;
	this->points.clear();
	this->points.shrink_to_fit();
	this->knns.clear();
	this->knns.shrink_to_fit();

	this->knnpPoints.clear();
	this->knnpPoints.shrink_to_fit();
	this->knnps.clear();
	this->knnps.shrink_to_fit();

	this->knnpNodes.clear();
	this->knnpNodes.shrink_to_fit();
	this->pNodes.clear();
	this->pNodes.shrink_to_fit();

	this->knnpNearestOnes.clear();
	this->knnpNearestOnes.shrink_to_fit();
	this->pNearestOnes.clear();
	this->pNearestOnes.shrink_to_fit();
}

void PKNN::BuildKNNs()
{
	parallel_for(size_t(0), size_t(N), [&](size_t idx) {
		vector<Point*> pointsBlock(&this->points[idx], &this->points[idx] + this->PP);
		this->knns.push_back(new KNN(this->K, this->NN, pointsBlock));
		});
}

void PKNN::SetKNNPPoints(concurrent_vector<Point*> points)
{
	this->knnpPoints = points;
	this->P = points.size();
	this->PP = this->P / this->N;
}

void PKNN::BuildKNNPs()
{
	parallel_for(size_t(0), size_t(N), [&](size_t idx) {
		concurrent_vector<Point*> pointsBlock(&this->knnpPoints[idx], &this->knnpPoints[idx] + this->PP);
		this->knnps.push_back(new KNNP(this->K, this->NN, pointsBlock));
		});
}

void PKNN::BuildKdTrees()
{
	parallel_for(size_t(0), size_t(N), [&](size_t idx) {
		this->knns[idx]->KDTree->SetRegion(this->region);
		this->knns[idx]->BuildKdTree();
		});
}

void PKNN::BuildPKdTrees()
{
	parallel_for(size_t(0), size_t(N), [&](size_t idx) {
		this->knnps[idx]->KDTree->SetRegion(this->region);
		this->knnps[idx]->BuildPKdTree();
		});
}

void PKNN::Search(KNN* knn, Node* node, Range* range, concurrent_vector<Node*>* nodes)
{
	if (node != NULL && node->boundingBox == NULL && node->point != NULL)
	{
		if (Utility::Contains(range, node->point)) {
			knn->nearestPoints.push_back(node->point);
			nodes->push_back(node);
		}
	}
	else {
		if (node != NULL && node->boundingBox != NULL && Utility::Contains(range, node->boundingBox->left->GetBounds())) {
			nodes->push_back(node->boundingBox->left);
		}
		else {
			if (node != NULL && node->boundingBox != NULL && Utility::Intersects(range, node->boundingBox->left->GetBounds())) {
				Search(knn, node->boundingBox->left, range, nodes);
			}
		}
		if (node != NULL && node->boundingBox != NULL && Utility::Contains(range, node->boundingBox->right->GetBounds())) {
			nodes->push_back(node->boundingBox->right);
		}
		else {
			if (node != NULL && node->boundingBox != NULL && Utility::Intersects(range, node->boundingBox->right->GetBounds())) {
				Search(knn, node->boundingBox->right, range, nodes);
			}
		}
		return;
	}
}

void PKNN::PSearch()
{
	parallel_for(size_t(0), size_t(N), [&](size_t idx) {
		this->Search(this->knns[idx], this->knns[idx]->KDTree->root, this->range, &this->pNodes);
		for (int idx = 0; idx < this->pNodes.size(); idx++) {
			this->Points(pNodes[idx], &this->pNearestOnes);
		}
		});
}

void PKNN::KNNPSearch()
{
	parallel_for(size_t(0), size_t(N), [&](size_t idx) {
		knnps[idx]->Search(this->knnps[idx]->KDTree->root, this->range, &this->knnpNodes);
		for (int idx = 0; idx < this->knnpNodes.size(); idx++) {
			this->KNNPPoints(knnpNodes[idx], &this->knnpNearestOnes);
		}
		});
}

void PKNN::Points(Node* root, concurrent_vector<Point*>* points)
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

void PKNN::KNNPPoints(Node* root, concurrent_vector<Point*>* points)
{
	if (root == NULL)
		return;
	if (root->boundingBox != NULL)
		KNNPPoints(root->boundingBox->left, points);
	if (root->point != NULL)
		points->push_back(root->point);
	if (root->boundingBox != NULL)
		KNNPPoints(root->boundingBox->right, points);
}

void PKNN::RemoveDuplicatePoints()
{
	set<Point*> uniquePoints(this->pNearestOnes.begin(), this->pNearestOnes.end());
	this->pNearestOnes.assign(uniquePoints.begin(), uniquePoints.end());
}

void PKNN::RemoveKNNPDuplicatePoints()
{
	set<Point*> uniquePoints(this->knnpNearestOnes.begin(), this->knnpNearestOnes.end());
	this->knnpNearestOnes.assign(uniquePoints.begin(), uniquePoints.end());
}
