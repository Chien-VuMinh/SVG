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



class Rec : public Shape {
protected:
	Point2D start;
	int height, width;
};


class _Rectangle : public Rec {
public:
	void SetRec(int* rgb, Point2D start, int height, int width, int thickness, int* fill_rgb, 
				double fill_opacity, double stroke_opacity, vector<Transform>& transform);
	void myLinearGradientBrush(HDC hdc, LinearGradient gradient);
	VOID OnPaint(HDC hdc);
};



//class RoundRectangle : public Rec {
//private:
//	int thickness;
//	Point2D end;
//
//public:
//	void SetRoundRec(HDC hdc, int* rgb, Point2D start, int height, int width, int thickness);
//
//	VOID OnPaintRoundRec();
//};
