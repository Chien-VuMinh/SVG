#include "stdafx.h"
#include "rapidxml.hpp"
#include "Line.h"



void Line::SetLine(int* rgb, Point2D start, Point2D end, int thickness, double stroke_opacity) 
{
    for (int i = 0; i <= 2; i++)
    {
        this->rgb[i] = rgb[i];
    }
    this->start = start;
    this->end = end;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
}

void Line::myLinearGradientBrush(double* firstrgb, double* secondrgb)
{
    Graphics graphics(hdc);
    LinearGradientBrush linearBrush(
        Point(50, 10), //associated with the first color
        Point(150, 10), //associated with the second color
        Color(255 * firstrgb[0], firstrgb[1], firstrgb[2], firstrgb[3]),
        Color(255 * secondrgb[0], secondrgb[1], secondrgb[2], secondrgb[3]));

    linearBrush.SetGammaCorrection(TRUE);
    Pen pen(&linearBrush);
    graphics.DrawLine(&pen, start.GetX(), start.GetY(), end.GetX(), end.GetY());
}

void Line::gradientBrushPath(double* firstrgb, double* secondrgb)
{
    // Create a path that consists of a single ellipse.
    Graphics graphics(this->hdc);
    GraphicsPath path;
    path.AddLine(start.GetX(), start.GetY(), end.GetX(), end.GetY());

    // Use the path to construct a brush.
    PathGradientBrush pthGrBrush(&path);
    pthGrBrush.SetGammaCorrection(TRUE);

    // Set the color at the center of the path to blue.
    pthGrBrush.SetCenterColor(Color(255 * firstrgb[0], firstrgb[1], firstrgb[2], firstrgb[3]));

    // Set the color along the entire boundary of the path to aqua.
    Color colors[] = { Color(255 * secondrgb[0], secondrgb[1], secondrgb[2], secondrgb[3]) };
    int count = 1;
    pthGrBrush.SetSurroundColors(colors, &count);
    Pen pen(&pthGrBrush);
    graphics.DrawLine(&pen, start.GetX(), start.GetY(), end.GetX(), end.GetY());
}

VOID Line::OnPaint(HDC hdc, double opacity) {
    Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
    graphics.DrawLine(&pen, start.GetX(), start.GetY(), end.GetX(), end.GetY());
}
