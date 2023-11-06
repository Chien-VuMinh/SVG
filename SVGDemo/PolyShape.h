#pragma once
#include "stdafx.h"
#include "rapidxml.hpp"
#include <iostream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "Point.h"


using namespace std;
using namespace rapidxml;
using namespace Gdiplus;


#pragma comment (lib,"Gdiplus.lib")



class PolyShape {
protected:
	HDC hdc;
	int rgb[3];
	int thickness;
	int NumOfPoint;
	PointF* points;

public:
	PolyShape();
	~PolyShape();

};


class PolyLine : public PolyShape {
public:
	void SetPolyLine(HDC hdc, int* rgb, int thickness, int NumOfPoint, Point2D* points);

	VOID OnPaintPolyLine();
};



class PolyGon : public PolyShape {
private:
	int brushRGB[3];
public:
	void SetPolyLine(HDC hdc, int* rgb, int* brushRGB, int thickness, int NumOfPoint, Point2D* points);

	VOID OnPaintPolyLine();
};