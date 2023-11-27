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


class Path : public Shape {
protected:
	int thickness;
	int fill_rgb[3];
	double fill_opacity;
	int NumOfLines;
	Point2D* Lines;
	int NumOfBeziers;
	Point2D* Beziers;

public:
	Path();

	void SetPath(int* rgb, int* fill_rgb, int thickness, int NumOfLines, Point2D* Lines,
				 int NumOfBeziers, Point2D* Beziers, double fill_opacity, double stroke_opacity);
	VOID OnPaint(HDC hdc);

	~Path();
};