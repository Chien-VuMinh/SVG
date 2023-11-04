#pragma once
#include <iostream>


using namespace std;

const double epsilon = 0.0001;

class Point2D {
private:
	int x, y;

public:
	Point2D();
	Point2D(int x, int y);

	int GetX();
	int GetY();

	~Point2D();
};