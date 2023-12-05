#include "stdafx.h"
#include "rapidxml.hpp"
#include "Line.h"



void Line::SetLine(int* rgb, Point2D start, Point2D end, int thickness, double stroke_opacity) 
{
    for (int i = 0; i <= 2; i++)
        this->rgb[i] = rgb[i];
    this->start = start;
    this->end = end;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
}


VOID Line::OnPaint(HDC hdc, vector<Transform>& transform) {
    Graphics graphics(hdc);
    int      alpha = 255 * stroke_opacity;
    Pen      pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);


    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
        {
            PointF center(transform[i].GetRotate()[1], transform[i].GetRotate()[2]);
            Gdiplus::Matrix	matrix;
            matrix.RotateAt(transform[i].GetRotate()[0], center);
            graphics.SetTransform(&matrix);
        }
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }


    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.DrawLine(&pen, start.GetX(), start.GetY(), end.GetX(), end.GetY());
}