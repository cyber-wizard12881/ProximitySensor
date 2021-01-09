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

//Class to hold the Range or Region (eg. 2-D Plane, 3-D Space or 1-D line .... etc....)
//[1,2] --> [4,8]
class KDTREE_API Range {
public:
	//Default Constructor
	Range();
	//Constructor
	Range(int K, vector<int> from, vector<int> to);
	//Destructor
	~Range();
	//Print the Range on the console
	void Plot();
	//Number of Dimensions
	int K;
	//Points from ....
	vector<int> from;
	//Points to .....
	vector<int> to;
};
