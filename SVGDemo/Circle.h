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


class Circle : public Shape {
protected:
	HDC hdc;
	int rgb[3];
	int fill_rgb[3];
	int thickness;
	Point2D center;
	int radX, radY;

	double stroke_opacity;
	double fill_opacity;
public:
	void SetCircle(HDC hdc, int* rgb, Point2D center, int radX, int radY, int thickness, int* fill_rgb, double stroke_opacity, double fill_opacity);

	VOID OnPaint();
};