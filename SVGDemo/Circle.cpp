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

    //SolidBrush solidBrush(Color(alpha, ((this->rgb[0] * alpha) / 255) + 255 * (255 - alpha) / 255, ((this->rgb[1] * alpha) / 255) + 255 * (255 - alpha) / 255, ((this->rgb[2] * alpha) / 255) + 255 * (255 - alpha) / 255));
    SolidBrush solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillEllipse(&solidBrush, this->getX() - this->getradX(), this->getY() - this->getradY(), this->getradX() * 2, this->getradY() * 2);
}


void Circle::myLinearGradientBrush(HDC hdc, double* firstrgb, double* secondrgb)//these arr need 4 elements (alpha, reb, green, blue)
{
    Graphics graphics(hdc);
    LinearGradientBrush linearBrush(
        Point(50, 10), //associated with the first color
        Point(150, 10), //associated with the second color
        Color(255 * firstrgb[0], firstrgb[1], firstrgb[2], firstrgb[3]),
        Color(255 * secondrgb[0], secondrgb[1], secondrgb[2], secondrgb[3]));

    linearBrush.SetGammaCorrection(TRUE);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillEllipse(&linearBrush, this->getX() - this->getradX(), this->getY() - this->getradY(), this->getradX() * 2, this->getradY() * 2);
}


void Circle::gradientBrushPath(HDC hdc, double* firstrgb, double* secondrgb)
{
    // Create a path that consists of a single ellipse.
    Graphics graphics(hdc);
    GraphicsPath path;
    path.AddEllipse(this->getX() - this->getradX(), this->getY() - this->getradY(), this->getradX() * 2, this->getradY() * 2);

    // Use the path to construct a brush.
    PathGradientBrush pthGrBrush(&path);
    pthGrBrush.SetGammaCorrection(TRUE);

    // Set the color at the center of the path to blue.
    pthGrBrush.SetCenterColor(Color(255 * firstrgb[0], firstrgb[1], firstrgb[2], firstrgb[3]));

    // Set the color along the entire boundary of the path to aqua.
    Color colors[] = { Color(255 * secondrgb[0], secondrgb[1], secondrgb[2], secondrgb[3]) };
    int count = 1;
    pthGrBrush.SetSurroundColors(colors, &count);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillEllipse(&pthGrBrush, this->getX() - this->getradX() + 100, this->getY() - this->getradY() + 100, this->getradX() * 2, this->getradY() * 2);
}


VOID Circle::OnPaint(HDC hdc) {
    Graphics   graphics(hdc);
    int        alpha = 255 * stroke_opacity;
    Pen        pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.DrawEllipse(&pen, center.GetX() - radX, center.GetY() - radY, 2 * radX, 2 * radY);
}

