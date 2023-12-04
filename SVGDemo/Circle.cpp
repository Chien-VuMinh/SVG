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

int Circle::getX()
{
    return this->center.GetX();
}

int Circle::getY()
{
    return this->center.GetY();
}

int Circle::getradX()
{
    return this->radX;
}

int Circle::getradY()
{
    return this->radY;
}

void Circle::setRGB(int* rgb)
{
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
}


void Circle::_fillCircle(HDC hdc)
{
    Graphics    graphics(hdc);
    int alpha = 255 * fill_opacity;

    SolidBrush solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillEllipse(&solidBrush, this->getX() - this->getradX(), this->getY() - this->getradY(), this->getradX() * 2, this->getradY() * 2);
}


VOID Circle::OnPaint(HDC hdc) {
    Graphics   graphics(hdc);
    int        alpha = 255 * fill_opacity;
    SolidBrush solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillEllipse(&solidBrush, center.GetX() - radX, center.GetY() - radY, 2 * radX, 2 * radY);

    alpha      = 255 * stroke_opacity;
    Pen        pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
    graphics.DrawEllipse(&pen, center.GetX() - radX, center.GetY() - radY, 2 * radX, 2 * radY);
}

