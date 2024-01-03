#pragma once
#include "stdafx.h"
#include "rapidxml.hpp"
#include <iostream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "Point.h"
#include "Shape.h"
#include "Transform.h"
#include "LinearGradient.h"

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;


#pragma comment (lib,"Gdiplus.lib")



class PolyShape : public Shape {
protected:
	int NumOfPoint;
	PointF* points;
	double fill_opacity;
	int fill_rgb[3];

public:
	PolyShape();
	~PolyShape();
};


class PolyLine : public PolyShape {
public:
	void SetPolyLine(int* rgb, int thickness, vector<Point2D> points, int* fill_rgb, 
					 double fill_opacity, double stroke_opacity, vector<Transform>& transform);
	void myLinearGradientBrush(HDC hdc, LinearGradient gradient);
	VOID OnPaint(HDC hdc);
};



class PolyGon : public PolyShape {
public:
	void SetPolyGon(int* rgb, int* fill_rgb, int thickness, vector<Point2D> points, 
					double fill_opacity, double stroke_opacity, vector<Transform>& transform);
	void myLinearGradientBrush(HDC hdc, LinearGradient gradient);
	VOID OnPaint(HDC hdc);
};
