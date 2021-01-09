#include "pch.h"
#include "Point.h"
#include <cstdarg>
#include <iostream>
#include <sstream>

using namespace std;

//Create the K-Dimensional Point!!!
Point::Point(int K, ...)
{
	int point;
	this->dimensions = K;
	this->cutDimension = 0;
	std::va_list val_point;
	va_start(val_point, K);
	for (int idx = 0; idx < K; ++idx) {
		point = va_arg(val_point, int);
		this->datum.push_back(point);
	}
	va_end(val_point);
}

//A Copy Constructor
Point::Point(const Point& point)
{
	this->dimensions = point.dimensions;
	this->datum = point.datum;
}

//A Clone Constructor
Point::Point(Point* point)
{
	this->cutDimension = point->cutDimension;
	vector<int> datum(point->datum);
	this->datum = datum;
	this->dimensions = point->dimensions;
}

//Default Constructor
Point::Point()
{
	this->dimensions = 0;
	this->cutDimension = 0;
	this->datum.clear();
}

//Pretty Print the Point's Contents onto the Console!!
void Point::Plot()
{
	stringstream ss;
	for (int idx = 0; idx < this->dimensions; idx++)
	{
		if (idx != 0)
			ss << ",";
		ss << this->datum[idx];
	}
	cout << "(" << ss.str() << ")" << endl;
}

//Destructor
Point::~Point()
{
	this->dimensions = 0;
	this->datum.clear();
	this->datum.shrink_to_fit();
}

//Operator Overloading for Comparision Friendliness!!!
bool operator==(const Point& lhs, const Point& rhs)
{
	if (lhs.dimensions != rhs.dimensions)
		return false;
	for (int idx = 0; idx < lhs.dimensions; idx++) {
		if (lhs.datum[idx] != rhs.datum[idx])
			return false;
	}
		return true;
}

//Operator Overloading for Sorting Friendliness!!!
bool operator<=(const Point& lhs, const Point& rhs)
{
	if (lhs.datum[lhs.cutDimension] <= rhs.datum[rhs.cutDimension]) {
		return true;
	}
	return false;
}
