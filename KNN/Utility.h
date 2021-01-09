#pragma once
#include <vector>
#include "Point.h"
#include "Node.h"
#include "Range.h"

#ifdef KNN_EXPORTS
#  define KNN_API __declspec(dllexport)
#else
#  define KNN_API __declspec(dllimport)
#endif

using namespace std;

//Utility Class for Checking Containment & Intersection of Points & Ranges in a Specified Region
class KNN_API Utility {
public:
	//Point Contained completely within a range?
	static bool Contains(Range* range, Point* point);
	//Bounding Box Contained Completely within a range?
	static bool Contains(Range* region, Range* bounds);
	//Bounding Box Intersects with a range?
	static bool Intersects(Range* region, Range* bounds);
};