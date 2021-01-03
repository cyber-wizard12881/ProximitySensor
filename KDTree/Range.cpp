#include "pch.h"
#include "Range.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>

Range::Range()
{
	this->K = 0;
	this->from.clear();
	this->to.clear();
}

Range::Range(int K, vector<int> from, vector<int> to)
{
	this->K = K;
	this->from = from;
	this->to = to;
}

Range::~Range()
{
	this->K = 0;
	this->from.clear();
	this->from.shrink_to_fit();
	this->to.clear();
	this->to.shrink_to_fit();
}

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
