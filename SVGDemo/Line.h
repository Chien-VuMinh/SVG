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


class Line : public Shape {
protected:
	int rgb[3];
	int thickness;
	Point2D start, end;
	double stroke_opacity;
public:
	void SetLine(int* rgb, Point2D start, Point2D end, int thickness, double stroke_opacity);
        void myLinearGradientBrush(HDC, double*, double*);
        void gradientBrushPath(HDC, double*, double*);

	VOID OnPaint(HDC hdc, double);
};
