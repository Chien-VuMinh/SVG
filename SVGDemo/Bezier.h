#pragma once
#include "stdafx.h"
#include "rapidxml.hpp"
#include <iostream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "Point.h"
#include "Shape.h"


using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")


class Bezier : public Shape {
protected:
	int thickness;
	PointF points[4];
	double fill_opacity;
	int fill_rgb[3];

public:
	Bezier();

	void SetBezier(int* rgb, int thickness, Point2D* points, int* fill_rgb, 
		             double fill_opacity, double stroke_opacity);
	VOID OnPaint(HDC hdc);

	~Bezier();
};