#include "stdafx.h"
#include "rapidxml.hpp"
#include "PolyShape.h"

PolyShape::PolyShape() {
    NumOfPoint = 0;
    points = NULL;
}


PolyShape::~PolyShape() {
    delete[] points;
}





void PolyLine::SetPolyLine(int* rgb, int thickness, vector<Point2D> points, int* fill_rgb, double fill_opacity,double stroke_opacity, vector<Transform>& transform) {
    this->thickness = thickness;
    this->NumOfPoint = points.size();
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;
    this->transform = transform;

    this->points = new PointF[NumOfPoint];
    for (int i = 0; i < NumOfPoint; ++i) {
        this->points[i].X = points[i].GetX();
        this->points[i].Y = points[i].GetY();
    }

    for (int i = 0; i <= 2; i++)
    {   
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}



void PolyLine::myLinearGradientBrush(HDC hdc, LinearGradient gradient) {
    Graphics graphics(hdc);
    GraphicsPath path;
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    path.AddLines(this->points, this->NumOfPoint);

    // Use the path to construct a brush.
    PathGradientBrush pthGrBrush(&path);
    pthGrBrush.SetGammaCorrection(TRUE);

    // Set the color at the center of the path to blue.
    pthGrBrush.SetCenterColor(Color(255 * fill_opacity, gradient.rgb1[0], gradient.rgb1[1], gradient.rgb1[2]));

    // Set the color along the entire boundary of the path to aqua.
    Color colors[] = { 255 * fill_opacity, gradient.rgb2[0], gradient.rgb2[1], gradient.rgb2[2] };
    int count = 1;
    pthGrBrush.SetSurroundColors(colors, &count);

    graphics.FillPolygon(&pthGrBrush, this->points, this->NumOfPoint);
}

void PolyLine::myLinearGradientBrush(HDC hdc, LinearGradient gradient) {
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
    graphics.FillPolygon(&linearBrush, this->points, this->NumOfPoint);
}

void PolyLine::OnPaint(HDC hdc) {
    Graphics     graphics(hdc);
    int          alpha = 255 * fill_opacity;
    SolidBrush   solidBrush(Color(alpha, fill_rgb[0], fill_rgb[1], fill_rgb[2]));


    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
            graphics.RotateTransform(transform[i].GetRotate()[0]);
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillPolygon(&solidBrush, points, NumOfPoint);

    if (thickness != 0) {
        alpha = 255 * stroke_opacity;
        Pen          pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);
        graphics.DrawLines(&pen, points, NumOfPoint);
    }
}







void PolyGon::SetPolyGon(int* rgb, int* fill_rgb, int thickness, vector<Point2D> points, double fill_opacity, double stroke_opacity, vector<Transform>& transform) {
    this->thickness = thickness;
    this->NumOfPoint = points.size();
    this->fill_opacity = fill_opacity;
    this->stroke_opacity = stroke_opacity;
    this->points = new PointF[NumOfPoint];
    this->transform = transform;
    for (int i = 0; i < NumOfPoint; ++i) {
        this->points[i].X = points[i].GetX();
        this->points[i].Y = points[i].GetY();
    }
    for (int i = 0; i <= 2; i++) {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}

void PolyGon::myLinearGradientBrush(HDC hdc, LinearGradient gradient){
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
    graphics.FillPolygon(&linearBrush, this->points, this->NumOfPoint); 
}

void PolyGon::OnPaint(HDC hdc) {
    Graphics    graphics(hdc);
    int         alpha = 255 * fill_opacity;
    SolidBrush  solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));



    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
            graphics.RotateTransform(transform[i].GetRotate()[0]);
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillPolygon(&solidBrush, this->points, this->NumOfPoint);

    if (thickness != 0) {
        alpha = 255 * stroke_opacity;
        Pen         pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);
        graphics.DrawPolygon(&pen, points, NumOfPoint);
    }
}

