#include "stdafx.h"
#include "rapidxml.hpp"
#include "Path.h"


Path::Path(){
    NumOfLines = NumOfBeziers = 0;
    Lines = Beziers = NULL;
}

Path::~Path() {
    delete[] Lines, Beziers;
}

void Path::SetPath(int* rgb, int* fill_rgb, int thickness, int NumOfLines, Point2D* Lines,
    int NumOfBeziers, Point2D* Beziers, double fill_opacity, double stroke_opacity) {

    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;

    for (int i = 0; i < 3; i++)
    {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }


    this->NumOfLines = NumOfLines;
    this->Lines = new Point2D[NumOfLines * 2];
    for (int i = 0; i < NumOfLines * 2; ++i)
        this->Lines[i] = Lines[i];


    this->NumOfBeziers = NumOfBeziers;
    this->Beziers = new Point2D[NumOfBeziers * 4];
    for (int i = 0; i < NumOfBeziers * 4; ++i)
        this->Beziers[i] = Beziers[i];
}



VOID Path::OnPaint(HDC hdc) {
    Graphics        graphics(hdc);
    GraphicsPath    Path;
    int alpha=      255 * fill_opacity;
    SolidBrush      solidBrush(Color(alpha, fill_rgb[0], fill_rgb[1], fill_rgb[2]));
    Pen             pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);

    for (int i = 0; i < NumOfLines; ++i)
        Path.AddLine(  Lines[i*2].GetX(),       Lines[i * 2].GetY(), 
                       Lines[i * 2 + 1].GetX(), Lines[i * 2 + 1].GetY());

    for (int i = 0; i < NumOfBeziers; ++i)
        Path.AddBezier(Lines[i * 4].GetX(),     Lines[i * 4].GetY(), 
                       Lines[i * 4 + 1].GetX(), Lines[i * 4 + 1].GetY(), 
                       Lines[i * 4 + 2].GetX(), Lines[i * 4 + 2].GetY(), 
                       Lines[i * 4 + 3].GetX(), Lines[i * 4 + 3].GetY());

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    if(fill_rgb[0] != 0 || fill_rgb[1] != 0 || fill_rgb[2] != 0)
        graphics.FillPath(&solidBrush, &Path);

    if (!thickness)
        graphics.DrawPath(&pen, &Path);
}
