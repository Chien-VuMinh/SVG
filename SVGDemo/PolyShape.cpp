#include "stdafx.h"
#include "rapidxml.hpp"
#include "PolyShape.h"

PolyShape::PolyShape() {
    NumOfPoint = 0;
    points = NULL;
}


PolyShape::~PolyShape() {
    delete[] points;
}





void PolyLine::SetPolyLine(HDC hdc, int* rgb, int thickness, int NumOfPoint, Point2D* points) {
    this->hdc = hdc;
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
    this->thickness = thickness;
    this->NumOfPoint = NumOfPoint;
    this->points = new PointF[NumOfPoint];
    for (int i = 0; i < NumOfPoint; ++i) {
        this->points[i].X = points[i].GetX();
        this->points[i].Y = points[i].GetY();
    }
}


VOID PolyLine::OnPaintPolyLine() {
	Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
	graphics.DrawPolygon(&pen, points, NumOfPoint);
}






void PolyGon::SetPolyLine(HDC hdc, int* rgb, int* brushRGB, int thickness, int NumOfPoint, Point2D* points) {
    this->hdc = hdc;
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
    this->brushRGB[0] = brushRGB[0];
    this->brushRGB[1] = brushRGB[1];
    this->brushRGB[2] = brushRGB[2];
    this->thickness = thickness;
    this->NumOfPoint = NumOfPoint;
    this->points = new PointF[NumOfPoint];
    for (int i = 0; i < NumOfPoint; ++i) {
        this->points[i].X = points[i].GetX();
        this->points[i].Y = points[i].GetY();
    }
}


VOID PolyGon::OnPaintPolyLine() {
    Graphics        graphics(hdc);
    Pen             pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
    SolidBrush      brush(Color(brushRGB[0], brushRGB[1], brushRGB[2]));
    graphics.DrawPolygon(&pen, points, NumOfPoint);
    graphics.FillPolygon(&brush, points, NumOfPoint);
}