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


class Text : public Shape {
protected:
	string text;
	int rgb[3];
	int size;
	Point2D start;

public:
	void SetText(string text, int* rgb, int size, Point2D start);
	VOID OnPaint(HDC hdc);
};
