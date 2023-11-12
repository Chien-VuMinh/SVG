#include "stdafx.h"
#include "rapidxml.hpp"
#include "Text.h"




void Text::SetText(string text, int* rgb, int size, Point2D start) {
    this->text = text;
    this->rgb[0] = rgb[0];
    this->rgb[1] = rgb[1];
    this->rgb[2] = rgb[2];
    this->start = start;
    this->size = size;
}


VOID Text::OnPaint(HDC hdc) {
    wstring widestr = wstring(text.begin(), text.end());
    const wchar_t* widecstr = widestr.c_str();

    Graphics    graphics(hdc);
    SolidBrush  brush(Color(rgb[0], rgb[1], rgb[2]));
    FontFamily  fontFamily(L"Times New Roman");
    Font        font(&fontFamily, size, FontStyleRegular, UnitPixel);
    int Y = start.GetY() - font.GetHeight(FontStyleRegular);

    int scale = fontFamily.GetEmHeight(FontStyleRegular) / font.GetHeight(FontStyleRegular);
    PointF      pointF(start.GetX(), Y + fontFamily.GetCellDescent(FontStyleRegular) / scale);
    graphics.DrawString(widecstr, -1, &font, pointF, NULL, &brush);
}
