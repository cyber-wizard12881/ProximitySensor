#pragma once
#include <stdarg.h>
#include <vector>

#ifdef KDTREE_EXPORTS
#  define KDTREE_API __declspec(dllexport)
#else
#  define KDTREE_API __declspec(dllimport)
#endif

using namespace std;

class KDTREE_API Point
{
public:
	Point(int K, ...);
	Point(const Point &point);
	Point(Point* point);
	Point();
	~Point();
	void Plot();	
	int dimensions;
	vector<int> datum;
	int cutDimension;
};

KDTREE_API bool operator==(const Point& lhs, const Point& rhs);
KDTREE_API bool operator<=(const Point& lhs, const Point& rhs);

