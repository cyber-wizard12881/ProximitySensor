#include "pch.h"
#include "Utility.h"

//Checks if a Point is contained within a Range
bool Utility::Contains(Range* range, Point* point)
{
	for (int idx = 0; idx < range->K; idx++) {
		if ((range->from[idx] <= point->datum[idx] && range->to[idx] >= point->datum[idx])) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

//Checks if a Range (Bounding Box) is contained within a specified Region Completely
bool Utility::Contains(Range* region, Range* bounds)
{
	for (int idx = 0; idx < region->K; idx++) {
		if ((region->from[idx] <= bounds->from[idx] && region->to[idx] >= bounds->to[idx])) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

//Checks if a Range (Bounding Box) overlaps (Intersects) within a specified Region at all
bool Utility::Intersects(Range* region, Range* bounds)
{
	for (int idx = 0; idx < region->K; idx++) {
		if ((bounds->to[idx] < region->from[idx] || bounds->from[idx] > region->to[idx])) {
			continue;
		}
		else {
			return true;
		}
	}
	return false;
}
