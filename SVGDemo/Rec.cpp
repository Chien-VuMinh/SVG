#include "stdafx.h"
#include "rapidxml.hpp"
#include "Rec.h"





void _Rectangle::SetRec(HDC hdc, int* rgb, Point2D start, int height, int width, int thickness) {
    this->hdc = hdc;
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
    this->start = start;
    this->height = height;
    this->width = width;
    this->thickness = thickness;
}


VOID _Rectangle::OnPaintRec() {
    Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
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