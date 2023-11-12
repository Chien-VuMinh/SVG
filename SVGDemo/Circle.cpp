#include "stdafx.h"
#include "rapidxml.hpp"
#include "Circle.h"


void Circle::SetCircle(int* rgb, Point2D center, int radX, int radY, int thickness, int* fill_rgb, double stroke_opacity, double fill_opacity) {
    this->center = center;
    this->radX = radX;
    this->radY = radY;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;
    for (int i = 0; i <= 2; i++)
    {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}


VOID Circle::OnPaint(HDC hdc) {
    Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
    graphics.DrawEllipse(&pen, center.GetX() - radX, center.GetY() - radY, 2 * radX, 2 * radY);
}

