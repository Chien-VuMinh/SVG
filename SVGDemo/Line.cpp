#include "stdafx.h"
#include "rapidxml.hpp"
#include "Line.h"



void Line::SetLine(int* rgb, Point2D start, Point2D end, int thickness, double stroke_opacity, vector<Transform>& transform) {
    for (int i = 0; i <= 2; i++)
        this->rgb[i] = rgb[i];
    this->start = start;
    this->end = end;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    this->transform = transform;
}



void Line::myLinearGradientBrush(HDC hdc, LinearGradient gradient) {
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
    Pen pen(&linearBrush);
    graphics.DrawLine(&pen, static_cast<float>(start.GetX()), start.GetY(), end.GetX(), end.GetY());
}


VOID Line::OnPaint(HDC hdc) {
    Graphics        graphics(hdc);
    GraphicsPath    Path;
    int             alpha = 255 * stroke_opacity;
    Pen             pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);


    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
            graphics.RotateTransform(transform[i].GetRotate()[0]);
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }


    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.DrawLine(&pen, static_cast<float>(start.GetX()), start.GetY(), end.GetX(), end.GetY());
}