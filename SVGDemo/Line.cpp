#include "stdafx.h"
#include "rapidxml.hpp"
#include "Line.h"



void Line::SetLine(HDC hdc, int* rgb, Point2D start, Point2D end, int thickness, double stroke_opacity) 
{
    this->hdc = hdc;
    for (int i = 0; i <= 2; i++)
    {
        this->rgb[i] = rgb[i];
    }
    this->start = start;
    this->end = end;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
}


VOID Line::OnPaintLine() {
    Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
    graphics.DrawLine(&pen, start.GetX(), start.GetY(), end.GetX(), end.GetY());
}