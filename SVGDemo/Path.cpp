#include "stdafx.h"
#include "rapidxml.hpp"
#include "Path.h"


Path::Path() {}

Path::~Path() {}

void Path::SetPath(int* rgb, int* fill_rgb, int thickness, vector<char> command,
                   vector<vector<Point2D>> points, double fill_opacity, double stroke_opacity) {

    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;

    for (int i = 0; i < 3; i++)
    {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }


    this->command = command;
    this->points  = points;
}



VOID Path::OnPaint(HDC hdc, vector<Transform>& transform) {
    Graphics        graphics(hdc);
    GraphicsPath    Path;
    double          alpha = 255 * fill_opacity;
    SolidBrush      solidBrush(Color(alpha, fill_rgb[0], fill_rgb[1], fill_rgb[2]));


    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
            graphics.RotateTransform(transform[i].GetRotate()[0]);
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }
        

    for (int i = 0; i < command.size(); ++i) {
        if (command[i] == 'c' || command[i] == 'C' || command[i] == 's' || command[i] == 'S') {
            Point* pts = new Point[points[i].size()];
            for (int k = 0; k < points[i].size(); ++k) {
                pts[k].X = points[i][k].GetX();
                pts[k].Y = points[i][k].GetY();
            }
            Path.AddBeziers(pts, points[i].size());
            delete[] pts;
        }
        else
            Path.AddLine(static_cast<float>(points[i][0].GetX()), static_cast<float>(points[i][0].GetY()),
                static_cast<float>(points[i][1].GetX()), static_cast<float>(points[i][1].GetY()));
    }


    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillPath(&solidBrush, &Path);

    if (thickness != 0) {
        alpha = 255 * stroke_opacity;
        Pen        pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
        graphics.DrawPath(&pen, &Path);
    }
}
