#include "stdafx.h"
#include "rapidxml.hpp"
#include "Shape.h"
#include "Line.h"
#include "Rec.h"
#include "Circle.h"
#include "Text.h"
#include "PolyShape.h"
#include <string>
#include <sstream>


Shape::Shape() {
    ShapeArrSize = 0;
    ShapeArr = NULL;
}





//VOID Shape::OnPaintLine(HDC hdc, int* rgb, int xStart, int yStart, int xEnd, int yEnd, int thickness) {
//    Graphics graphics(hdc);
//    Pen      pen(Color(rgb[0], rgb[1], rgb[2]), thickness);
//    graphics.DrawLine(&pen, xStart, yStart, xEnd, yEnd);
//}


VOID Shape::OnPaintImage(HDC hdc, string name, int x, int y) {
    Graphics    graphics(hdc);

    wstring widestr = wstring(name.begin(), name.end());
    const wchar_t* widecstr = widestr.c_str();

    Bitmap bmp(widecstr);
    graphics.DrawImage(&bmp, x, y);
}


VOID Shape::OnPain(HDC hdc) {
    //int rgb[] = { 255, 0, 0 };

    //this->RecArr[0].OnPaintRec();
    //this->CircleArr[0].OnPaintCircle();
    //this->TextArr[0].OnPaintText();

    //OnPaintLine(hdc, rgb, 50, 125, 500, 125, 8);

    ////OnPaintString(hdc, "ThaNg NaO k0 Tai vE xEm t gHi v0 Ba0 cA0", rgb, 50, 50, 500);

    //rgb[1] = 255;
    ////OnPaintLine(hdc, rgb, 50, 125, 500, 300, 8);
    //this->LineArr[0].OnPaintLine();
    ////Line l;
    ////Point2D start(50, 125), end(500, 300);
    ////l.SetLine(hdc, rgb, start, end, 8);
    ////l.OnPaintLine();

    //rgb[2] = 100;
    //OnPaintLine(hdc, rgb, 500, 300, 550 / 2, 0, 8);

    //rgb[0] = 0;
    //OnPaintLine(hdc, rgb, 550 / 2, 0, 50, 300, 8);

    //rgb[1] = 0;
    //OnPaintLine(hdc, rgb, 50, 300, 500, 125, 8);
    


    //for (int i = 0; i < ShapeArrSize; ++i)
    //    ShapeArr[i]->OnPaint();

    //OnPaintImage(hdc, "33.png", 600, 10);


    //int rgb[] = { 255, 0, 0 };
    //Shape **s;
    //s = new Shape * [1];
    //Circle c;
    //Point2D start(50, 125), end(500, 300);
    //c.SetCircle(hdc, rgb, start, 10, 10, 5, rgb, 0.4, 0.3);
    //s[0] = &c;
    //s[0]->OnPaint();
}


VOID Shape::OnPaint(HDC hdc) {}


Shape::~Shape() {
    delete[] ShapeArr;
}











//VOID Example_DrawCurve2(HDC hdc)
//{
//    Graphics graphics(hdc);
//
//    // Define a Pen object and an array of Point objects.
//    Pen greenPen(Color::Green, 3);
//    Point point1(100, 100);
//    Point point2(200, 50);
//    Point point3(400, 10);
//    Point point4(500, 100);
//
//    Point curvePoints[4] = {
//    point1,
//    point2,
//    point3,
//    point4 };
//
//    Point* pcurvePoints = curvePoints;
//
//    // Specify offset, number of segments to draw, and tension.
//    int offset = 1;
//    int segments = 2;
//    REAL tension = 1.0;
//
//    // Draw the curve.
//    graphics.DrawCurve(&greenPen, curvePoints, 4, offset, segments, tension);
//
//    //Draw the points in the curve.
//    SolidBrush redBrush(Color::Red);
//    graphics.FillEllipse(&redBrush, Rect(95, 95, 10, 10));
//    graphics.FillEllipse(&redBrush, Rect(195, 45, 10, 10));
//    graphics.FillEllipse(&redBrush, Rect(395, 5, 10, 10));
//    graphics.FillEllipse(&redBrush, Rect(495, 95, 10, 10));
//}
//
//
//
//
//
//
//
//VOID Example_DrawPolygon(HDC hdc)
//{
//    Graphics graphics(hdc);
//
//
//    // Create a Pen object.
//    Pen blackPen(Color(255, 0, 0, 0), 3);
//
//    // Create an array of Point objects that define the polygon.
//    Point point1(100, 100);
//    Point point2(200, 130);
//    Point point3(150, 200);
//    Point point4(50, 200);
//    Point point5(0, 130);
//    Point points[5] = { point1, point2, point3, point4, point5 };
//    Point* pPoints = points;
//
//    // Draw the polygon.
//    graphics.DrawPolygon(&blackPen, pPoints, 5);
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Shape        shape;
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        shape.HandleSVGFile(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
