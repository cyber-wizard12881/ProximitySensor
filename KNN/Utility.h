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

class KNN_API Utility {
public:
	static bool Contains(Range* range, Point* point);
	static bool Contains(Range* region, Range* bounds);
	static bool Intersects(Range* region, Range* bounds);
};