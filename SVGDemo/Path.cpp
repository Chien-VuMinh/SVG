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



VOID Path::OnPaint(HDC hdc) {
    Graphics        graphics(hdc);
    GraphicsPath    Path;
    int alpha=      255 * fill_opacity;
    SolidBrush      solidBrush(Color(alpha, fill_rgb[0], fill_rgb[1], fill_rgb[2]));

    //for (int i = 0; i < NumOfLines; ++i)
    //    Path.AddLine(  Lines[i*2].GetX(),       Lines[i * 2].GetY(), 
    //                   Lines[i * 2 + 1].GetX(), Lines[i * 2 + 1].GetY());

    //for (int i = 0; i < NumOfBeziers; ++i)
    //    Path.AddBezier(Lines[i * 4].GetX(),     Lines[i * 4].GetY(), 
    //                   Lines[i * 4 + 1].GetX(), Lines[i * 4 + 1].GetY(), 
    //                   Lines[i * 4 + 2].GetX(), Lines[i * 4 + 2].GetY(), 
    //                   Lines[i * 4 + 3].GetX(), Lines[i * 4 + 3].GetY());

    for (int i = 0; i < command.size(); ++i) {      
        if (command[i] == 'c' || command[i] == 'C') {
            Point* pts = new Point[points[i].size()];
            for (int k = 0; k < points[i].size(); ++k) {
                pts[k].X = points[i][k].GetX();
                pts[k].Y = points[i][k].GetY();
            }
            Path.AddBeziers(pts, points[i].size());
            delete[] pts;
        }
        else
            Path.AddLine(points[i][0].GetX(), points[i][0].GetY(),
                points[i][1].GetX(), points[i][1].GetY());
    }
        

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.FillPath(&solidBrush, &Path);

    alpha      = 255 * stroke_opacity;
    Pen        pen(Color(alpha, this->rgb[0], this->rgb[1], this->rgb[2]), this->thickness);
    graphics.DrawPath(&pen, &Path);
}
