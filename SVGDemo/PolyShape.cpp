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

void PolyLine::fillPoline(HDC hdc, double opacity)
{
    Graphics    graphics(hdc);
    int alpha = 255 * opacity;

    //SolidBrush solidBrush(Color(alpha, ((this->rgb[0] * alpha) / 255) + 255 * (255 - alpha) / 255, ((this->rgb[1] * alpha) / 255) + 255 * (255 - alpha) / 255, ((this->rgb[2] * alpha) / 255) + 255 * (255 - alpha) / 255));
    SolidBrush solidBrush(Color(255 * opacity, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    graphics.FillPolygon(&solidBrush, this->points, this->NumOfPoint);
}

void PolyLine::gradientBrushPath(double* firstrgb, double* secondrgb)
{
    Graphics graphics(hdc);
    LinearGradientBrush linearBrush(
        Point(50, 10), //associated with the first color
        Point(150, 10), //associated with the second color
        Color(255 * firstrgb[0], firstrgb[1], firstrgb[2], firstrgb[3]),
        Color(255 * secondrgb[0], secondrgb[1], secondrgb[2], secondrgb[3]));

    linearBrush.SetGammaCorrection(TRUE);
    graphics.FillPolygon(&linearBrush, this->points, this->NumOfPoint);
}

void PolyLine::myLinearGradientBrush(double* firstrgb, double* secondrgb)
{
    // Create a path that consists of a single ellipse.
    Graphics graphics(this->hdc);
    GraphicsPath path;
    path.AddLines(this->points, this->NumOfPoint);

    // Use the path to construct a brush.
    PathGradientBrush pthGrBrush(&path);
    pthGrBrush.SetGammaCorrection(TRUE);

    // Set the color at the center of the path to blue.
    pthGrBrush.SetCenterColor(Color(255 * firstrgb[0], firstrgb[1], firstrgb[2], firstrgb[3]));

    // Set the color along the entire boundary of the path to aqua.
    Color colors[] = { Color(255 * secondrgb[0], secondrgb[1], secondrgb[2], secondrgb[3]) };
    int count = 1;
    pthGrBrush.SetSurroundColors(colors, &count);

    graphics.FillPolygon(&pthGrBrush, this->points, this->NumOfPoint);
}

VOID PolyLine::OnPaint(HDC hdc, double stroke_opacity) {
	Graphics graphics(hdc);
    	int alpha = 255 * stroke_opacity;
	Pen      pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
	Line l;
	Point2D p1, p2;
	for (int i = 0; i < this->NumOfPoint; ++i)
	{
    		p1.SetPoint(this->points[i].X, this->points[i].Y), p2.SetPoint(this->points[i + 1].X, this->points[i + 1].Y);
    		l.SetLine(this->rgb, p1, p2, this->thickness, stroke_opacity);
    	l.OnPaint(hdc, stroke_opacity);
	}
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

void PolyGon::fillPolygon(HDC hdc, double opacity)
{
    Graphics    graphics(hdc);
    int alpha = 255 * opacity;

    //SolidBrush solidBrush(Color(alpha, ((this->rgb[0] * alpha) / 255) + 255 * (255 - alpha) / 255, ((this->rgb[1] * alpha) / 255) + 255 * (255 - alpha) / 255, ((this->rgb[2] * alpha) / 255) + 255 * (255 - alpha) / 255));
    SolidBrush solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    graphics.FillPolygon(&solidBrush, this->points, this->NumOfPoint);
}

void PolyGon::gradientBrushPath(double* firstrgb, double* secondrgb)
{
    Graphics graphics(hdc);
    LinearGradientBrush linearBrush(
        Point(50, 10), //associated with the first color
        Point(150, 10), //associated with the second color
        Color(255 * firstrgb[0], firstrgb[1], firstrgb[2], firstrgb[3]),
        Color(255 * secondrgb[0], secondrgb[1], secondrgb[2], secondrgb[3]));

    linearBrush.SetGammaCorrection(TRUE);
    graphics.FillPolygon(&linearBrush, this->points, this->NumOfPoint);
}

void PolyGon::myLinearGradientBrush(double* firstrgb, double* secondrgb)
{
    // Create a path that consists of a single ellipse.
    Graphics graphics(this->hdc);
    GraphicsPath path;
    path.AddPolygon(this->points, this->NumOfPoint);

    // Use the path to construct a brush.
    PathGradientBrush pthGrBrush(&path);
    pthGrBrush.SetGammaCorrection(TRUE);

    // Set the color at the center of the path to blue.
    pthGrBrush.SetCenterColor(Color(255 * firstrgb[0], firstrgb[1], firstrgb[2], firstrgb[3]));

    // Set the color along the entire boundary of the path to aqua.
    Color colors[] = { Color(255 * secondrgb[0], secondrgb[1], secondrgb[2], secondrgb[3]) };
    int count = 1;
    pthGrBrush.SetSurroundColors(colors, &count);

    graphics.FillPolygon(&pthGrBrush, this->points, this->NumOfPoint);
}

VOID PolyGon::OnPaint(HDC hdc, double stroke_opacity) {
    Graphics        graphics(hdc);
    int alpha = 255 * stroke_opacity;
    Pen      pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
    //Pen             pen(Color(255 * stroke_opacity, rgb[0], rgb[1], rgb[2]), thickness);
    graphics.DrawPolygon(&pen, points, NumOfPoint);
}
