#include "pch.h"
#include "Sorter.h"
#include <algorithm>

vector<Point*> Sorter::Sort(vector<Point*> points, int cutDimension)
{
	sort(points.begin(), points.end(), [cutDimension](const Point* lhs, const Point* rhs)
		{
			return lhs->datum[cutDimension] < rhs->datum[cutDimension];
		});
	return points;
}

pair<vector<Point*>, vector<Point*>> Sorter::Split(vector<Point*> points, Point* median, int cutDimension)
{
	vector<Point*> leftOnes;
	vector<Point*> rightOnes;
	leftOnes.clear();
	rightOnes.clear();
	for (Point* point : points) {
		if (point->datum[cutDimension] <= median->datum[cutDimension]) {
			leftOnes.push_back(point);
		}
		else {
			rightOnes.push_back(point);
		}
	}
	return make_pair(leftOnes, rightOnes);
}

Point* Sorter::FindMedian(vector<Point*> points)
{
	int size = points.size();
	if (size < 1) {
		return NULL;
	}
	int middleOne = (size - 1) / 2;
	return points[middleOne];
}

Point* Sorter::FindMin(vector<Point*> points, int cutDimension)
{
	vector<Point*> sortedOnes = Sort(points, cutDimension);
	return sortedOnes[0];
}

Point* Sorter::FindMax(vector<Point*> points, int cutDimension)
{
	vector<Point*> sortedOnes = Sort(points, cutDimension);
	return sortedOnes[sortedOnes.size()-1];
}


concurrent_vector<Point*> Sorter::Sort(concurrent_vector<Point*> points, int cutDimension)
{
	sort(points.begin(), points.end(), [cutDimension](const Point* lhs, const Point* rhs)
		{
			return lhs->datum[cutDimension] < rhs->datum[cutDimension];
		});
	return points;
}

pair<concurrent_vector<Point*>, concurrent_vector<Point*>> Sorter::Split(concurrent_vector<Point*> points, Point* median, int cutDimension)
{
	concurrent_vector<Point*> leftOnes;
	concurrent_vector<Point*> rightOnes;
	leftOnes.clear();
	rightOnes.clear();
	for (Point* point : points) {
		if (point->datum[cutDimension] <= median->datum[cutDimension]) {
			leftOnes.push_back(point);
		}
		else {
			rightOnes.push_back(point);
		}
	}
	return make_pair(leftOnes, rightOnes);
}

Point* Sorter::FindMedian(concurrent_vector<Point*> points)
{
	int size = points.size();
	if (size < 1) {
		return NULL;
	}
	int middleOne = (size - 1) / 2;
	return points[middleOne];
}

Point* Sorter::FindMin(concurrent_vector<Point*> points, int cutDimension)
{
	concurrent_vector<Point*> sortedOnes = Sort(points, cutDimension);
	return sortedOnes[0];
}

Point* Sorter::FindMax(concurrent_vector<Point*> points, int cutDimension)
{
	concurrent_vector<Point*> sortedOnes = Sort(points, cutDimension);
	return sortedOnes[sortedOnes.size() - 1];
}
