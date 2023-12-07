#pragma once
#include "stdafx.h"
#include "rapidxml.hpp"
#include <iostream>


class Point2D {
private:
	double x, y;

public:
	Point2D();
	Point2D(double x, double y);

	double GetX();
	double GetY();
	void SetPoint(double x, double y);

	~Point2D();
};