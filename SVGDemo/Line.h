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


class Line : public Shape {
protected:
	Point2D start, end;

public:
	void SetLine(int* rgb, Point2D start, Point2D end, int thickness, double stroke_opacity, vector<Transform>& transform);
	void myLinearGradientBrush(HDC hdc, LinearGradient gradient);
	VOID OnPaint(HDC hdc);
};
