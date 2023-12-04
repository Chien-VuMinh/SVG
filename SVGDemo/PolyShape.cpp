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





void PolyLine::SetPolyLine(int* rgb, int thickness, vector<Point2D> points, int* fill_rgb, double fill_opacity,double stroke_opacity) {
    this->thickness = thickness;
    this->NumOfPoint = points.size();
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;
    
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

void PolyLine::OnPaint(HDC hdc)
{
    Graphics     graphics(hdc);
    int alpha    = 255 * fill_opacity;
    SolidBrush   solidBrush(Color(alpha, fill_rgb[0], fill_rgb[1], fill_rgb[2]));
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillPolygon(&solidBrush, points, NumOfPoint);

    alpha        = 255 * stroke_opacity;
    Pen          pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);
    graphics.DrawLines(&pen, points, NumOfPoint);
}

//VOID PolyLine::OnPaint(HDC hdc) {
//    if (!thickness)
//        return;
//	Graphics     graphics(hdc);
//    int          alpha = 255 * stroke_opacity;
//	Pen          pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);
//    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
//	graphics.DrawLines(&pen, points, NumOfPoint);
//}






void PolyGon::SetPolyGon(int* rgb, int* fill_rgb, int thickness, vector<Point2D> points, double fill_opacity, double stroke_opacity) {
    this->thickness = thickness;
    this->NumOfPoint = points.size();
    this->fill_opacity = fill_opacity;
    this->stroke_opacity = stroke_opacity;
    this->points = new PointF[NumOfPoint];
    for (int i = 0; i < NumOfPoint; ++i) {
        this->points[i].X = points[i].GetX();
        this->points[i].Y = points[i].GetY();
    }
    for (int i = 0; i <= 2; i++) {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}

void PolyGon::OnPaint(HDC hdc)
{
    Graphics    graphics(hdc);
    int         alpha = 255 * fill_opacity;
    SolidBrush  solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillPolygon(&solidBrush, this->points, this->NumOfPoint);


    alpha       = 255 * stroke_opacity;
    Pen         pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
    graphics.DrawPolygon(&pen, points, NumOfPoint);
}

//VOID PolyGon::OnPaint(HDC hdc) {
//    Graphics    graphics(hdc);
//    int         alpha = 255 * stroke_opacity;
//    Pen         pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
//    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
//    graphics.DrawPolygon(&pen, points, NumOfPoint);
//}
