#pragma once
#include <vector>
#include "Point.h"

#ifdef KDTREE_EXPORTS
#  define KDTREE_API __declspec(dllexport)
#else
#  define KDTREE_API __declspec(dllimport)
#endif

using namespace std;

class KDTREE_API Sorter {
public:
	static vector<Point*> Sort(vector<Point*> points, int cutDimension);
	static pair<vector<Point*>, vector<Point*>> Split(vector<Point*> points, Point* median, int cutDimension);
	static Point* FindMedian(vector<Point*> points);
	static Point* FindMin(vector<Point*> points, int cutDimension);
	static Point* FindMax(vector<Point*> points, int cutDimension);
};