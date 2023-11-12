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





void PolyLine::SetPolyLine(int* rgb, int thickness, int NumOfPoint, Point2D* points, int* fill_rgb, double fill_opacity,double stroke_opacity) {
    this->thickness = thickness;
    this->NumOfPoint = NumOfPoint;
    this->stroke_opacity = stroke_opacity;
    
    this->points = new PointF[NumOfPoint];
    for (int i = 0; i < NumOfPoint; ++i) {
        this->points[i].X = points[i].GetX();
        this->points[i].Y = points[i].GetY();
    }

    for (int i = 0; i <= 2; i++)
    {   
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}


VOID PolyLine::OnPaint(HDC hdc) {
	Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
	graphics.DrawPolygon(&pen, points, NumOfPoint);
}






void PolyGon::SetPolyLine(int* rgb, int* fill_rgb, int thickness, int NumOfPoint, Point2D* points, double fill_opacity, double stroke_opacity) {
    this->thickness = thickness;
    this->NumOfPoint = NumOfPoint;
    this->fill_opacity = fill_opacity;
    this->stroke_opacity = stroke_opacity;
    this->points = new PointF[NumOfPoint];
    for (int i = 0; i < NumOfPoint; ++i) {
        this->points[i].X = points[i].GetX();
        this->points[i].Y = points[i].GetY();
    }
    for (int i = 0; i <= 2; i++)
    {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}


VOID PolyGon::OnPaint(HDC hdc) {
    Graphics        graphics(hdc);
    Pen             pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
    SolidBrush      brush(Color(fill_rgb[0], fill_rgb[1], fill_rgb[2]));
    graphics.DrawPolygon(&pen, points, NumOfPoint);
    graphics.FillPolygon(&brush, points, NumOfPoint);
}