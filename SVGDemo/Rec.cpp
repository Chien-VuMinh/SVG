#include "stdafx.h"
#include "rapidxml.hpp"
#include "Rec.h"





void _Rectangle::SetRec(int* rgb, Point2D start, int height, int width, int thickness, int* fill_rgb, double fill_opacity, double stroke_opacity, vector<Transform>& transform) {
    this->start = start;
    this->height = height;
    this->width = width;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;
    this->transform = transform;

    for (int i = 0; i <= 2; i++)
    {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}

void _Rectangle::myLinearGradientBrush(HDC hdc, LinearGradient gradient)
{
    Graphics graphics(hdc);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
            graphics.RotateTransform(transform[i].GetRotate()[0]);
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }

    LinearGradientBrush linearBrush(
        Point(gradient.p1.GetX(), gradient.p1.GetY()),
        Point(gradient.p2.GetX(), gradient.p2.GetY()),
        Color(255 * fill_opacity, gradient.rgb1[0], gradient.rgb1[1], gradient.rgb1[2]),
        Color(255 * fill_opacity, gradient.rgb2[0], gradient.rgb2[1], gradient.rgb2[2]));

    linearBrush.SetGammaCorrection(TRUE);
    graphics.FillRectangle(&linearBrush, start.GetX(), start.GetY(), width, height);
}

VOID _Rectangle::OnPaint(HDC hdc) {
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

    if (thickness != 0) {
        graphics.DrawRectangle(&pen, start.GetX(), start.GetY(), width, height);
    }

    alpha = 255 * fill_opacity;
    SolidBrush     solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    graphics.FillRectangle(&solidBrush, start.GetX(), start.GetY(), width, height);
}
