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
#include "Transform.h"
#include "LinearGradient.h"


using namespace std;
using namespace rapidxml;
using namespace Gdiplus;


#pragma comment (lib,"Gdiplus.lib")

class Shape {
protected:
	int rgb[3];
	int fill_rgb[3];
	int thickness;
	double fill_opacity;
	double stroke_opacity;
	vector<Transform> transform;

public:
	Shape();

	void ReadSVGFile(HDC hdc, string file_name);
	void HanleSVG(HDC hdc, xml_node<>*& root);
	void Draw(HDC hdc, xml_node<>*& root, int* fill, double fill_opacity, int* stroke_fill,
		      double stroke_opacity, int thickness, vector<Transform> transform, 
			  vector<LinearGradient> gradient,int font_size);
	void readTransform(string value, vector<Transform>& transform);

	void readRGB(string value, int* rgb);
	void GetP(vector<vector<Point2D>>& points, string s, int& n, Point2D startP);

	virtual VOID OnPaint(HDC hdc);

	~Shape();
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
