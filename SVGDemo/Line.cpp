#include "stdafx.h"
#include "rapidxml.hpp"
#include "Line.h"



void Line::SetLine(HDC hdc, int* rgb, Point2D start, Point2D end, int thickness) {
    this->hdc = hdc;
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
    this->start = start;
    this->end = end;
    this->thickness = thickness;
}


VOID Line::OnPaintLine() {
    Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
    graphics.DrawLine(&pen, start.GetX(), start.GetY(), end.GetX(), end.GetY());
}