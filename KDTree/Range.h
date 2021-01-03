#pragma once
#include <vector>
#include "Point.h"
#include "Node.h"

#ifdef KDTREE_EXPORTS
#  define KDTREE_API __declspec(dllexport)
#else
#  define KDTREE_API __declspec(dllimport)
#endif

using namespace std;

class KDTREE_API Range {
public:
	Range();
	Range(int K, vector<int> from, vector<int> to);
	~Range();
	void Plot();
	int K;
	vector<int> from;
	vector<int> to;
};
