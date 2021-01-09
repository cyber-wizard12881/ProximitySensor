#include "pch.h"
#include "Sorter.h"
#include <algorithm>

//Serial Container's Sort
vector<Point*> Sorter::Sort(vector<Point*> points, int cutDimension)
{
	sort(points.begin(), points.end(), [cutDimension](const Point* lhs, const Point* rhs)
		{
			return lhs->datum[cutDimension] < rhs->datum[cutDimension];
		});
	return points;
}

//Split the Point Vector into 2 parts based on the mid-point!!!!
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

//Find the Median of the Serial Container
Point* Sorter::FindMedian(vector<Point*> points)
{
	int size = points.size();
	if (size < 1) {
		return NULL;
	}
	int middleOne = (size - 1) / 2;
	return points[middleOne];
}

//Find the Min of the Serial Container
Point* Sorter::FindMin(vector<Point*> points, int cutDimension)
{
	vector<Point*> sortedOnes = Sort(points, cutDimension);
	return sortedOnes[0];
}

//Find the Max of the Serial Container
Point* Sorter::FindMax(vector<Point*> points, int cutDimension)
{
	vector<Point*> sortedOnes = Sort(points, cutDimension);
	return sortedOnes[sortedOnes.size()-1];
}

//Sort the Parallel Container
concurrent_vector<Point*> Sorter::Sort(concurrent_vector<Point*> points, int cutDimension)
{
	sort(points.begin(), points.end(), [cutDimension](const Point* lhs, const Point* rhs)
		{
			return lhs->datum[cutDimension] < rhs->datum[cutDimension];
		});
	return points;
}

//Split the Parallel Container's Point Vector into 2 parts based on the mid-point!!!!
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

//Median of the Parallel Container?
Point* Sorter::FindMedian(concurrent_vector<Point*> points)
{
	int size = points.size();
	if (size < 1) {
		return NULL;
	}
	int middleOne = (size - 1) / 2;
	return points[middleOne];
}

//Min Value of the Parallel Container?
Point* Sorter::FindMin(concurrent_vector<Point*> points, int cutDimension)
{
	concurrent_vector<Point*> sortedOnes = Sort(points, cutDimension);
	return sortedOnes[0];
}

//Max Value of the Parallel Container?
Point* Sorter::FindMax(concurrent_vector<Point*> points, int cutDimension)
{
	concurrent_vector<Point*> sortedOnes = Sort(points, cutDimension);
	return sortedOnes[sortedOnes.size() - 1];
}
