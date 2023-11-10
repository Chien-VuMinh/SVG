#include "stdafx.h"
#include "rapidxml.hpp"
#include "Shape.h"
#include <string>


Shape::Shape() {
    LineArrSize = 0;
    LineArr = NULL;

    RecArrSize = 0;
    RecArr = NULL;

    CircleArrSize = 0;
    CircleArr = NULL;

    TextArrSize = 0;
    TextArr = NULL;

    PolyLineArrSize = 0;
    PolyLineArr = NULL;

    PolyGonArrSize = 0;
    PolyGonArr = NULL;
}


void Shape::ReadSVG(HDC hdc) {
    //this->LineArrSize = 1;
    //int rgb[] = { 255,255, 0 };
    //Point2D start(50, 125), end(500, 300);

    //this->LineArr = new Line[LineArrSize];

    //this->LineArr[0].SetLine(hdc, rgb, start, end, 8);



    //this->RecArrSize = 1;
    //this->RecArr = new _Rectangle[RecArrSize];

    //this->RecArr[0].SetRec(hdc, rgb, start, 100, 500, 8);



    //this->CircleArrSize = 1;
    //this->CircleArr = new Circle[CircleArrSize];
    //start.SetPoint(747, 163);
    //rgb[2] = 255;
    //rgb[0] = 1;
    //this->CircleArr[0].SetCircle(hdc, rgb, start, 107, 107, 8);


    //this->TextArrSize = 1;
    //this->TextArr = new Text[TextArrSize];
    //start.SetPoint(50, 500);
    //rgb[2] = 0;
    //rgb[1] = 0;
    //rgb[0] = 255;
    //this->TextArr[0].SetText(hdc, "ThaNg NaO k0 Tai vE xEm t gHi v0 Ba0 cA0", rgb, 50, start);






    // READING SVG FILE START FROM HERE
    ifstream ifs;
    ifs.open("Sample.svg");
    if (!ifs.is_open())
        cout << "Cannot open file!" << endl;
    string temp;
    while (getline(ifs, temp, '\n'))
    {
        if (temp.find("rect") < temp.size())
        {
            RecArrSize++;
        }
        else if (temp.find("circle") < temp.length() || temp.find("ellipse") < temp.length())
        {
            CircleArrSize++;
        }
        else if (temp.find("text") < temp.length())
        {
            TextArrSize++;
        }
        else if (temp.find("polyline") < temp.length())
        {
            PolyLineArrSize++;
        }
        else if (temp.find("polygon") < temp.length())
        {
            PolyGonArrSize++;
        }
        else if (temp.find("line") < temp.length())
        {
            LineArrSize++;
        }
    }
    ifs.close();

    RecArr = new _Rectangle[RecArrSize];
    CircleArr = new Circle[CircleArrSize];
    TextArr = new Text[TextArrSize];
    PolyLineArr = new PolyLine[PolyLineArrSize];
    PolyGonArr = new PolyGon[PolyGonArrSize];
    LineArr = new Line[LineArrSize];
    int countRec = 0;
    ifstream In;
    In.open("Sample.svg");
    if (In.is_open() == 0)
        cout << "Cannot open this file!";
    while (getline(In, temp, '\n'))
    {
        if (temp.find("rect") < temp.size())
        {
           
            int pos1 = temp.find("fill-opacity") + 14;
            int pos2 = temp.find("\"", pos1);
            double fill_opacity = stod(temp.substr(pos1, pos2-pos1));
            
            pos1 = temp.find("stroke=") + 13;
            pos2 = temp.find(",", pos1);
            int rgb[3];
            rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

            pos1 = pos2 + 1;
            pos2 = temp.find(",", pos1);
            rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));
            
            pos1 = pos2 + 1;
            pos2 = temp.find(")", pos1);
            rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            
            pos1 = temp.find("stroke-width=") + 14;
            pos2 = temp.find("\"", pos1);
            int thickness = stoi(temp.substr(pos1, pos2 - pos1));

            Point2D start;
            pos1 = temp.find("x=") + 3;
            pos2 = temp.find("\"", pos1);
            int x = stoi(temp.substr(pos1, pos2 - pos1));

            pos1 = temp.find("y=") + 3;
            pos2 = temp.find("\"", pos1);
            int y = stoi(temp.substr(pos1, pos2 - pos1));
            start.SetPoint(x, y);

            pos1 = temp.find("width=") + 7;
            pos2 = temp.find("\"", pos1);
            int width = stoi(temp.substr(pos1, pos2 - pos1));

            pos1 = temp.find("height=") + 8;
            pos2 = temp.find("\"", pos1);
            int height = stoi(temp.substr(pos1, pos2 - pos1));

            pos1 = temp.find("fill=") + 10;
            pos2 = temp.find(",", pos1);
            int fill_rgb[3];
            fill_rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

            pos1 = pos2 + 1;
            pos2 = temp.find(",", pos1);
            fill_rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

            pos1 = pos2 + 1;
            pos2 = temp.find(")", pos1);
            fill_rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));

            pos1 = temp.find("stroke-width=") + 14;
            pos2 = temp.find("\"", pos1);
            int thickness = stoi(temp.substr(pos1, pos2 - pos1));

            if (temp.find("stroke-opacity") < temp.size())
            {
                //pos1 = temp.find()
            }

            //RecArr[countRec++].SetRec(hdc, rgb, start, height, width, thickness, fill_rgb, fill_opacity, )
        }
        else if (temp.find("circle") < temp.length() || temp.find("ellipse") < temp.length())
        {
            CircleArrSize++;
        }
        else if (temp.find("text") < temp.length())
        {
            TextArrSize++;
        }
        else if (temp.find("polyline") < temp.length())
        {
            PolyLineArrSize++;
        }
        else if (temp.find("polygon") < temp.length())
        {
            PolyGonArrSize++;
        }
        else if (temp.find("line") < temp.length())
        {
            LineArrSize++;
        }
    }
    ifs.close();

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


    OnPaintImage(hdc, "33.png", 600, 10);
}


Shape::~Shape() {
    delete[] LineArr, RecArr, CircleArr, TextArr, PolyLineArr, PolyGonArr;
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