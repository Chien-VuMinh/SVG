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



class PolyShape : public Shape {
protected:
	int rgb[3];
	int thickness;
	int NumOfPoint;
	PointF* points;
	double stroke_opacity;
	double fill_opacity;
	int fill_rgb[3];
public:
	PolyShape();
	~PolyShape();

};


class PolyLine : public PolyShape {
public:
	void SetPolyLine(int* rgb, int thickness, int NumOfPoint, Point2D* points, int* fill_rgb, double fill_opacity, double stroke_opacity);

	VOID OnPaint(HDC hdc);
};



class PolyGon : public PolyShape {
public:
	void SetPolyLine(int* rgb, int* fill_rgb, int thickness, int NumOfPoint, Point2D* points, double fill_opacity, double stroke_opacity);

	VOID OnPaint(HDC hdc);
};