#include "stdafx.h"
#include "rapidxml.hpp"
#include "Circle.h"


void Circle::SetCircle(HDC hdc, int* rgb, Point2D center, int radX, int radY, int thickness) {
    this->hdc = hdc;
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
    this->center = center;
    this->radX = radX;
    this->radY = radY;
    this->thickness = thickness;
}


VOID Circle::OnPaintCircle() {
    Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
    graphics.DrawEllipse(&pen, center.GetX() - radX, center.GetY() - radY, 2 * radX, 2 * radY);
}