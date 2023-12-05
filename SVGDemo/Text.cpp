#include "stdafx.h"
#include "rapidxml.hpp"
#include "Text.h"




void Text::SetText(string text, int* rgb, int size, Point2D start, int* fill, double stroke_opacity, double fill_opacity, int thickness) {
    this->text = text;
    this->start = start;
    this->size = size;
    this->thickness = thickness;
    this->stroke_opacity = stroke_opacity;
    this->fill_opacity = fill_opacity;
    for (int i = 0; i < 3; ++i) {
        this->rgb[i] = rgb[i];
        this->fill_rgb[i] = fill[i];
    }
}


VOID Text::OnPaint(HDC hdc, vector<Transform>& transform) {
    wstring widestr = wstring(text.begin(), text.end());
    const wchar_t* widecstr = widestr.c_str();

    Graphics    graphics(hdc);
    SolidBrush  brush(Color(fill_opacity * 255, rgb[0], rgb[1], rgb[2]));
    Pen         pen(Color((stroke_opacity * 255), this->fill_rgb[0], this->fill_rgb[1], this->fill_rgb[2]));
    FontFamily  fontFamily(L"Times New Roman");
    Font        font(&fontFamily, size, FontStyleRegular, UnitPixel);
    int         Y = start.GetY() - font.GetHeight(FontStyleRegular);
    int         scale = fontFamily.GetEmHeight(FontStyleRegular) / font.GetHeight(FontStyleRegular);
    PointF      pointF(start.GetX(), Y + fontFamily.GetCellDescent(FontStyleRegular) / scale);

    for (int i = 0; i < transform.size(); i++) {
        if (transform[i].GetName() == "t")
            graphics.TranslateTransform(transform[i].GetTranslate()[0], transform[i].GetTranslate()[1]);
        if (transform[i].GetName() == "r")
            graphics.RotateTransform(transform[i].GetRotate()[0]);
        if (transform[i].GetName() == "s")
            graphics.ScaleTransform(transform[i].GetScale()[0], transform[i].GetScale()[1]);
    }


    //PointF pointF(start.GetX(), start.GetY());
    // Create a GraphicsPath
    GraphicsPath path;

    // Add the string to the path
    path.AddString(widestr.c_str(), -1, &fontFamily, FontStyleRegular, static_cast<REAL>(size), pointF, NULL);

    // Create a solid brush for filling
    
    // Fill the path with the solid brush
    graphics.FillPath(&brush, &path);
    if (thickness != 0)
        graphics.DrawPath(&pen, &path);



    //graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    //graphics.DrawString(widecstr, -1, &font, pointF, NULL, &brush);
}
