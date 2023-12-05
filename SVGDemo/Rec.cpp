#include "stdafx.h"
#include "rapidxml.hpp"
#include "Rec.h"





void _Rectangle::SetRec(int* rgb, Point2D start, int height, int width, int thickness, int* fill_rgb, double fill_opacity, double stroke_opacity) {
    this->start = start;
    this->height = height;
    this->width = width;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;
    for (int i = 0; i <= 2; i++)
    {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}


VOID _Rectangle::OnPaint(HDC hdc, vector<Transform>& transform) {
    Graphics       graphics(hdc);
    double         alpha = 255 * stroke_opacity;
    Pen            pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);


    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
            graphics.RotateTransform(transform[i].GetRotate()[0]);
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }


    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.DrawRectangle(&pen, start.GetX(), start.GetY(), width, height);

    alpha          = 255 * fill_opacity;
    SolidBrush     solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    graphics.FillRectangle(&solidBrush, start.GetX(), start.GetY(), width, height);
}