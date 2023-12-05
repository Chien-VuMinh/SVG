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



VOID Path::OnPaint(HDC hdc, vector<Transform> transform) {
    Graphics   graphics(hdc);
    int        alpha = 255 * fill_opacity;
    SolidBrush solidBrush(Color(alpha, this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));


    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
            graphics.RotateTransform(transform[i].GetRotate()[0]);
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }
        

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillPath(&solidBrush, &Path);

    alpha      = 255 * stroke_opacity;
    Pen        pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
    graphics.DrawPath(&pen, &Path);
}
