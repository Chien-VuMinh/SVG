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

	int Translate[2];
	int Scale[2];
	int rgb[3];
	double stroke_opacity;

public:
	Shape();

	void ReadSVGFile(HDC hdc, string file_name);
	void HanleSVG(HDC hdc, xml_node<>*& root);
	void Draw(HDC hdc, xml_node<>*& root, int* fill, double fill_opacity, int* stroke_fill,
		      double stroke_opacity, int* translate, int* scale, int rotate);
	void readTransform(string value, int*& translate, int*& scale, int& rotate);

	void readRGB(string value, int*& rgb);
	void GetP(vector<vector<Point2D>>& points, string s, int& n, Point2D startP);

	virtual VOID OnPaint(HDC hdc, double);
	virtual void fillRect(HDC, double);
	virtual void _fillCircle(HDC, double);
	virtual void fillPoline(HDC, double);
	virtual void fillPolygon(HDC, double);

	~Shape();
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
