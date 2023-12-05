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

using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")


class Path : public Shape {
protected:
	int thickness;
	int fill_rgb[3];
	double fill_opacity;
	vector<char> command;
	vector<vector<Point2D>> points;

public:
	Path();

	void SetPath(int* rgb, int* fill_rgb, int thickness, vector<char> command,
				 vector<vector<Point2D>> points, double fill_opacity, double stroke_opacity);
	VOID OnPaint(HDC hdc, vector<Transform>& transform);

	~Path();
};
