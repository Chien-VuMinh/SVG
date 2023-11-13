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

class Shape {
protected:
	int ShapeArrSize;
	Shape** ShapeArr;

public:
	Shape();

	void HandleSVGFile(HDC hdc);

	VOID OnPaintLine(HDC hdc, int* rgb, int xStart, int yStart, int xEnd, int yEnd, int thickness);
	VOID OnPaintString(HDC hdc, string s, int* rgb, int size, int x, int y);
	VOID OnPaintImage(HDC hdc, string name, int x, int y);
	virtual VOID OnPain(HDC hdc);
	virtual VOID OnPaint(HDC hdc, double);
	virtual void fillRect(HDC, double);
	virtual void _fillCircle(HDC, double);
	virtual void fillPoline(HDC, double);
	virtual void fillPolygon(HDC, double);


	~Shape();
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
