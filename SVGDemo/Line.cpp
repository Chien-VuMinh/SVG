#include "stdafx.h"
#include "rapidxml.hpp"
#include "Line.h"



void Line::SetLine(int* rgb, Point2D start, Point2D end, int thickness, double stroke_opacity) 
{
    for (int i = 0; i <= 2; i++)
        this->rgb[i] = rgb[i];
    this->start = start;
    this->end = end;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
}


VOID Line::OnPaint(HDC hdc) {
    Graphics graphics(hdc);
    int      alpha = 255 * stroke_opacity;
    Pen      pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.DrawLine(&pen, start.GetX(), start.GetY(), end.GetX(), end.GetY());
}
