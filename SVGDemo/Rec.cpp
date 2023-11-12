#include "stdafx.h"
#include "rapidxml.hpp"
#include "Rec.h"





void _Rectangle::SetRec(int* rgb, Point2D start, int height, int width, int thickness, int* fill_rgb, double fill_opacity, double stroke_opacity) {
    this->start = start;
    this->height = height;
    this->width = width;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    for (int i = 0; i <= 2; i++)
    {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}

int _Rectangle::getHeight()
{
    return this->height;
}

int _Rectangle::getWidth()
{
    return this->width;
}

int _Rectangle::getX()
{
    return this->start.GetX();
}

int _Rectangle::getY()
{
    return this->start.GetY();
}

void _Rectangle::setRGB(double* rgb)
{
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
}

void _Rectangle::fillRect(HDC hdc, double opacity)
{
    Graphics    graphics(hdc);
    int alpha = 255 * opacity;

    //SolidBrush solidBrush(Color(alpha, ((this->rgb[0] * alpha) / 255) + 255 * (255 - alpha) / 255, ((this->rgb[1] * alpha) / 255) + 255 * (255 - alpha) / 255, ((this->rgb[2] * alpha) / 255) + 255 * (255 - alpha) / 255));
    SolidBrush solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    graphics.FillRectangle(&solidBrush, start.GetX(), start.GetY(), width, height);
}

VOID _Rectangle::OnPaint(HDC hdc, double stroke_opacity) {
    Graphics graphics(hdc);
    int alpha = 255 * stroke_opacity;
    Pen      pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
    graphics.DrawRectangle(&pen, start.GetX(), start.GetY(), width, height);
}



//void RoundRectangle::SetRoundRec(HDC hdc, int* rgb, Point2D start, int height, int width, int thickness) {
//    this->hdc = hdc;
//    this->rgb[0] = rgb[0];
//    this->rgb[1] = rgb[1];
//    this->rgb[2] = rgb[2];
//    this->start = start;
//    this->height = height;
//    this->width = width;
//    this->thickness = thickness;
//}
//
//VOID RoundRectangle::OnPaintRoundRec() {
//    Graphics graphics(hdc);
//    RoundRect(hdc, start.GetX(), start.GetY(), 100, 100, 10, 10);
//}
