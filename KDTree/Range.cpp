#include "pch.h"
#include "Range.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>

//Create Default Range
Range::Range()
{
	this->K = 0;
	this->from.clear();
	this->to.clear();
}

//Create a Range Object with K Dimensions ... [1,2,3] -> [5,6,7] for instance....
Range::Range(int K, vector<int> from, vector<int> to)
{
	this->K = K;
	this->from = from;
	this->to = to;
}

//Destructor
Range::~Range()
{
	this->K = 0;
	this->from.clear();
	this->from.shrink_to_fit();
	this->to.clear();
	this->to.shrink_to_fit();
}

//Pretty Print the Range onto the Console!!!
void Range::Plot()
{
	std::ostringstream fromStr;
	std::copy(from.begin(), from.end(), std::ostream_iterator<int>(fromStr, ","));
	std::string fromRange(fromStr.str());

	std::ostringstream toStr;
	std::copy(to.begin(), to.end(), std::ostream_iterator<int>(toStr, ","));
	std::string toRange(toStr.str());

	cout << "Range is: [" << fromRange.substr(0, fromRange.size() - 1) << "] --> [" << toRange.substr(0, toRange.size() - 1) << "] " << endl;
}
