#pragma once
#include "stdafx.h"
#include "rapidxml.hpp"
#include <iostream>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include <fstream>
#include "Point.h"


using namespace std;
using namespace rapidxml;
using namespace Gdiplus;


#pragma comment (lib,"Gdiplus.lib")


class Line {
private:
	HDC hdc;
	int rgb[3];
	int thickness;
	Point2D start, end;

public:
	void SetLine(HDC hdc, int* rgb, Point2D start, Point2D end, int thickness);

	VOID OnPaintLine();
};