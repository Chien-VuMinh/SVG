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



class Rec : public Shape {
protected:
	HDC hdc;
	int rgb[3];
	Point2D start;
	int height, width;
	double fill_opacity;
	int fill_rgb[3];
	double stroke_opacity;
};


class _Rectangle : public Rec {
private:
	int thickness;

public:
	void SetRec(HDC hdc, int* rgb, Point2D start, int height, int width, int thickness, int* fill_rgb, double fill_opacity, double stroke_opacity);

	VOID OnPaint();
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