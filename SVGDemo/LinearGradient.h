#pragma once
#include "Point.h"


struct LinearGradient {
	string id;
	Point2D p1, p2;
	int rgb1[3], rgb2[3];
};