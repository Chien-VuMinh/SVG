#include "Bezier.h"


Bezier::Bezier(){}

Bezier::~Bezier() {}

void Bezier::SetBezier(int* rgb, int thickness, Point2D* points, int* fill_rgb,
	double fill_opacity, double stroke_opacity) {
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;

    for (int i = 0; i < 4; ++i) {
        this->points[i].X = points[i].GetX();
        this->points[i].Y = points[i].GetY();
    }

    for (int i = 0; i < 3; i++)
    {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill_rgb[i];
    }
}


VOID Bezier::OnPaint(HDC hdc) {
    if (!thickness)
        return;
    Graphics     graphics(hdc);
    GraphicsPath bezierPath;
    int alpha=   255 * fill_opacity;
    SolidBrush   solidBrush(Color(alpha, fill_rgb[0], fill_rgb[1], fill_rgb[2]));
    Pen          pen(Color(alpha, rgb[0], rgb[1], rgb[2]), thickness);

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    bezierPath.AddBeziers(points, 4);
    graphics.FillPath(&solidBrush, &bezierPath);
    graphics.DrawPath(&pen, &bezierPath);
}
