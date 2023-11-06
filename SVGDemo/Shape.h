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
#include "Line.h"
#include "Rec.h"
#include "Circle.h"
#include "Text.h"
#include "PolyShape.h"


using namespace std;
using namespace rapidxml;
using namespace Gdiplus;


#pragma comment (lib,"Gdiplus.lib")

class Shape {
private:
	int LineArrSize;
	Line* LineArr;

	int RecArrSize;
	_Rectangle* RecArr;

	int CircleArrSize;
	Circle* CircleArr;

	int TextArrSize;
	Text* TextArr;

	int PolyLilneArrSize;
	PolyLine* PolyLineArr;

	int PolyGonArrSize;
	PolyGon* PolyGonArr;


public:
	Shape();

	void ReadSVG(HDC hdc);

	VOID OnPaintLine(HDC hdc, int* rgb, int xStart, int yStart, int xEnd, int yEnd, int thickness);
	VOID OnPaintString(HDC hdc, string s, int* rgb, int size, int x, int y);
	VOID OnPaintImage(HDC hdc, string name, int x, int y);
	VOID OnPain(HDC hdc);

	~Shape();
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);