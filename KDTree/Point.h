#pragma once
#include <stdarg.h>
#include <vector>

#ifdef KDTREE_EXPORTS
#  define KDTREE_API __declspec(dllexport)
#else
#  define KDTREE_API __declspec(dllimport)
#endif

using namespace std;

//Class to hold the K-Dimensional Point Info
class KDTREE_API Point
{
public:
	//The K-Dimensional Point Constructor
	Point(int K, ...);
	//The Copy Constructor
	Point(const Point &point);
	//The Overloaded Point clone Constructor
	Point(Point* point);
	//Default Constructor
	Point();
	//The Destructor
	~Point();
	//Print the Point Info on the console
	void Plot();
	//Number of Dimensions of the point
	int dimensions;
	//The Point Data ... eg.  (3,7)
	vector<int> datum;
	//The Dimension to cut the point eg. X, Y etc...
	int cutDimension;
};

//Overloaded Operator for equality comparision
KDTREE_API bool operator==(const Point& lhs, const Point& rhs);
//Overloaded Operator for less than or equal to comparision ... for sorting .... 
KDTREE_API bool operator<=(const Point& lhs, const Point& rhs);

