#include "stdafx.h"
#include "rapidxml.hpp"
#include "Shape.h"


Shape::Shape() {
    LineArrSize = 0;
    LineArr = NULL;
}


void Shape::ReadSVG(HDC hdc) {
    this->LineArrSize = 1;
    int rgb[] = { 255,255, 0 };
    Point2D start(50, 125), end(500, 300);

    this->LineArr = new Line[LineArrSize];

    this->LineArr[0].SetLine(hdc, rgb, start, end, 8);
}


VOID Shape::OnPaintLine(HDC hdc, int* rgb, int xStart, int yStart, int xEnd, int yEnd, int thickness) {
    //Ref: https://docs.microsoft.com/en-us/windows/desktop/gdiplus/-gdiplus-getting-started-use
    Graphics graphics(hdc);
    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
    graphics.DrawLine(&pen, xStart, yStart, xEnd, yEnd);
}



VOID Shape::OnPaintString(HDC hdc, string s, int* rgb, int size, int x, int y) {
    wstring widestr = wstring(s.begin(), s.end());
    const wchar_t* widecstr = widestr.c_str();



    Graphics    graphics(hdc);
    SolidBrush  brush(Color(rgb[0], rgb[1], rgb[2]));
    FontFamily  fontFamily(L"Times New Roman");
    Font        font(&fontFamily, 50, FontStyleRegular, UnitPixel);
    PointF      pointF(x, y);

    graphics.DrawString(widecstr, -1, &font, pointF, &brush);
}


VOID Shape::OnPaintImage(HDC hdc, string name, int x, int y) {
    Graphics    graphics(hdc);

    wstring widestr = wstring(name.begin(), name.end());
    const wchar_t* widecstr = widestr.c_str();

    Bitmap bmp(widecstr);
    graphics.DrawImage(&bmp, x, y);
}


VOID Shape::OnPain(HDC hdc) {
    int rgb[] = { 255, 0, 0 };
    OnPaintLine(hdc, rgb, 50, 125, 500, 125, 8);

    OnPaintString(hdc, "ThaNg NaO k0 Tai vE xEm t gHi v0 Ba0 cA0", rgb, 70, 50, 500);

    rgb[1] = 255;
    //OnPaintLine(hdc, rgb, 50, 125, 500, 300, 8);
    this->LineArr[0].OnPaintLine();
    //Line l;
    //Point2D start(50, 125), end(500, 300);
    //l.SetLine(hdc, rgb, start, end, 8);
    //l.OnPaintLine();

    rgb[2] = 100;
    OnPaintLine(hdc, rgb, 500, 300, 550 / 2, 0, 8);

    rgb[0] = 0;
    OnPaintLine(hdc, rgb, 550 / 2, 0, 50, 300, 8);

    rgb[1] = 0;
    OnPaintLine(hdc, rgb, 50, 300, 500, 125, 8);


    OnPaintImage(hdc, "33.png", 600, 10);
}


Shape::~Shape() {
    delete[] LineArr;
}









LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Shape        shape;
    HDC          hdc;
    PAINTSTRUCT  ps;


    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        shape.ReadSVG(hdc);
        shape.OnPain(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}