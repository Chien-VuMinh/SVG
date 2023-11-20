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


void Shape::HandleSVGFile(HDC hdc) {
    ifstream In;
    string temp;
    In.open("Sample.svg");


    while (getline(In, temp, '\n'))
    {
        if (temp.find("rect") < temp.size())
        {
            int pos1, pos2;
            double fill_opacity;
            if (temp.find("fill-opacity") < temp.length())
            {
                pos1 = temp.find("fill-opacity") + 14;
                pos2 = temp.find("\"", pos1);
                fill_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                fill_opacity = 1;
            }

            int rgb[3];
            if (temp.find("stroke=") < temp.length())
            {
                pos1 = temp.find("stroke=") + 12;
                pos2 = temp.find(",", pos1);

                rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                rgb[0] = rgb[1] = rgb[2] = 0;
            }

            Point2D start;
            int x, y;
            if (temp.find("x=") < temp.length())
            {
                pos1 = temp.find("x=") + 3;
                pos2 = temp.find("\"", pos1);
                x = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = temp.find(" y=") + 4;
                pos2 = temp.find("\"", pos1);
                y = stoi(temp.substr(pos1, pos2 - pos1));
                start.SetPoint(x, y);
            }
            else
            {
                start.SetPoint(0, 0);
            }

            int width;
            if (temp.find(" width=") < temp.length())
            {
                pos1 = temp.find(" width=") + 8;
                pos2 = temp.find("\"", pos1);
                width = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                width = 0;
            }

            int height;
            if (temp.find(" height=") < temp.length())
            {
                pos1 = temp.find(" height=") + 9;
                pos2 = temp.find("\"", pos1);
                height = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                height = 0;
            }

            int fill_rgb[3];
            if (temp.find("fill=") < temp.length())
            {
                pos1 = temp.find("fill=") + 10;
                pos2 = temp.find(",", pos1);

                fill_rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                fill_rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                fill_rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                fill_rgb[0] = fill_rgb[1] = fill_rgb[2] = 0;
            }

            int thickness;
            if (temp.find("stroke-width") < temp.length())
            {
                pos1 = temp.find("stroke-width=") + 14;
                pos2 = temp.find("\"", pos1);
                thickness = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                thickness = 0;
            }

            double stroke_opacity;
            if (temp.find("stroke-opacity") < temp.size())
            {
                pos1 = temp.find("stroke-opacity=") + 16;
                pos2 = temp.find("\"", pos1);
                stroke_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
                stroke_opacity = 1;

            _Rectangle Rec;
            Rec.SetRec(rgb, start, height, width, thickness, fill_rgb, fill_opacity, stroke_opacity);
            Rec.fillRect(hdc);
            Rec.OnPaint(hdc);

        }
        else if (temp.find("circle") < temp.length() || temp.find("ellipse") < temp.length())
        {
            Point2D center;
            int pos1, pos2;
            int cx, cy;
            if (temp.find("cx=") < temp.length())
            {
                pos1 = temp.find("cx=") + 4;
                pos2 = temp.find("\"", pos1);
                cx = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = temp.find("cy=") + 4;
                pos2 = temp.find("\"", pos1);
                cy = stoi(temp.substr(pos1, pos2 - pos1));
                center.SetPoint(cx, cy);
            }
            else
            {
                center.SetPoint(0, 0);
            }

            int radX, radY;
            if (temp.find("r=") < temp.length())
            {
                pos1 = temp.find("r=") + 3;
                pos2 = temp.find("\"", pos1);
                radX = radY = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else if (temp.find("rx=") < temp.length())
            {
                pos1 = temp.find("rx=") + 4;
                pos2 = temp.find("\"", pos1);
                radX = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = temp.find("ry=") + 4;
                pos2 = temp.find("\"", pos1);
                radY = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
                radX = radY = 0;

            int rgb[3];
            if (temp.find("stroke=") < temp.length())
            {
                pos1 = temp.find("stroke=") + 12;
                pos2 = temp.find(",", pos1);

                rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                rgb[0] = rgb[1] = rgb[2] = 0;
            }

            int fill_rgb[3];
            if (temp.find("fill=") < temp.length())
            {
                pos1 = temp.find("fill=") + 10;
                pos2 = temp.find(",", pos1);

                fill_rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                fill_rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                fill_rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                fill_rgb[0] = fill_rgb[1] = fill_rgb[2] = 0;
            }

            int thickness;
            if (temp.find("stroke-width") < temp.length())
            {
                pos1 = temp.find("stroke-width=") + 14;
                pos2 = temp.find("\"", pos1);
                thickness = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                thickness = 0;
            }

            double stroke_opacity;
            if (temp.find("stroke-opacity") < temp.size())
            {
                pos1 = temp.find("stroke-opacity=") + 16;
                pos2 = temp.find("\"", pos1);
                stroke_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
                stroke_opacity = 1;

            double fill_opacity;
            if (temp.find("fill-opacity") < temp.length())
            {
                pos1 = temp.find("fill-opacity") + 14;
                pos2 = temp.find("\"", pos1);
                fill_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                fill_opacity = 1;
            }
            Circle Cir;
            Cir.SetCircle(rgb, center, radX, radY, thickness, fill_rgb, stroke_opacity, fill_opacity);
            Cir._fillCircle(hdc);
            Cir.OnPaint(hdc);
        }
        else if (temp.find("text") < temp.length())
        {
            int pos1, pos2;
            Point2D start;
            int x, y;
            if (temp.find("x=") < temp.length())
            {
                pos1 = temp.find("x=") + 3;
                pos2 = temp.find("\"", pos1);
                x = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = temp.find(" y=") + 4;
                pos2 = temp.find("\"", pos1);
                y = stoi(temp.substr(pos1, pos2 - pos1));
                start.SetPoint(x, y);
            }
            else
            {
                start.SetPoint(0, 0);
            }

            int rgb[3];
            if (temp.find("fill=") < temp.length())
            {
                pos1 = temp.find("fill=") + 10;
                pos2 = temp.find(",", pos1);

                rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                rgb[0] = rgb[1] = rgb[2] = 0;
            }

            int size;
            if (temp.find("font-size=") < temp.length())
            {
                pos1 = temp.find("font-size=") + 11;
                pos2 = temp.find("\"", pos1);
                size = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                size = 0;
            }

            string txt;
            if (temp.find(">") < temp.length())
            {
                pos1 = temp.find(">") + 1;
                pos2 = temp.find("<", pos1);
                txt = temp.substr(pos1, pos2 - pos1);
            }
            else
            {
                txt = "";
            }

            Text text;
            text.SetText(txt, rgb, size, start);
            text.OnPaint(hdc);

        }
        else if (temp.find("polyline") < temp.length())
        {
            int pos1, pos2;
            int rgb[3];
            if (temp.find("stroke=") < temp.length())
            {
                pos1 = temp.find("stroke=") + 12;
                pos2 = temp.find(",", pos1);

                rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                rgb[0] = rgb[1] = rgb[2] = 0;
            }

            int thickness;
            if (temp.find("stroke-width") < temp.length())
            {
                pos1 = temp.find("stroke-width=") + 14;
                pos2 = temp.find("\"", pos1);
                thickness = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                thickness = 0;
            }

            int fill_rgb[3];
            if (temp.find("fill=") < temp.length())
            {
                pos1 = temp.find("fill=") + 10;
                pos2 = temp.find(",", pos1);

                fill_rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                fill_rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                fill_rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                fill_rgb[0] = fill_rgb[1] = fill_rgb[2] = 0;
            }

            double fill_opacity;
            if (temp.find("fill-opacity") < temp.length())
            {
                pos1 = temp.find("fill-opacity") + 14;
                pos2 = temp.find("\"", pos1);
                fill_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                fill_opacity = 1;
            }

            double stroke_opacity;
            if (temp.find("stroke-opacity") < temp.size())
            {
                pos1 = temp.find("stroke-opacity=") + 16;
                pos2 = temp.find("\"", pos1);
                stroke_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                stroke_opacity = 1;
            }
            string points;
            int NumOfPoint = 0;
            Point2D* pointsArray = NULL;
            vector<Point2D> pointArray;
            if (temp.find("points=") < temp.size())
            {
                pos1 = temp.find("points=") + 8;
                pos2 = temp.find("\"", pos1);
                points = temp.substr(pos1, pos2 - pos1);
                stringstream ss(points);
                string point;
                
                while (getline(ss, point, ' ')) {
                    stringstream pointSS(point);
                    string coordinate;
                    vector<int> coordinates;

                    while (getline(pointSS, coordinate, ','))
                        coordinates.push_back(stoi(coordinate));

                    Point2D pointObj(coordinates[0], coordinates[1]);
                    pointArray.push_back(pointObj);
                }

                NumOfPoint = pointArray.size();
                pointsArray = new Point2D[NumOfPoint];
                for (int i = 0; i < NumOfPoint; i++)
                    pointsArray[i] = pointArray[i];
            }
            else
            {
                NumOfPoint = 0;
                Point2D* pointsArray = NULL;
            }
            PolyLine Polyline;
            Polyline.SetPolyLine(rgb, thickness, NumOfPoint, pointsArray, fill_rgb, fill_opacity, stroke_opacity);
            Polyline.fillPoline(hdc);
            Polyline.OnPaint(hdc);

            delete[] pointsArray;
        }
        else if (temp.find("polygon") < temp.length())
        {

            int pos1, pos2;
            int rgb[3];
            if (temp.find("stroke=") < temp.length())
            {
                pos1 = temp.find("stroke=") + 12;
                pos2 = temp.find(",", pos1);

                rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                rgb[0] = rgb[1] = rgb[2] = 0;
            }

            int thickness;
            if (temp.find("stroke-width") < temp.length())
            {
                pos1 = temp.find("stroke-width=") + 14;
                pos2 = temp.find("\"", pos1);
                thickness = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                thickness = 0;
            }

            int fill_rgb[3];
            if (temp.find("fill=") < temp.length())
            {
                pos1 = temp.find("fill=") + 10;
                pos2 = temp.find(",", pos1);

                fill_rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                fill_rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                fill_rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                fill_rgb[0] = fill_rgb[1] = fill_rgb[2] = 0;
            }

            double fill_opacity;
            if (temp.find("fill-opacity") < temp.length())
            {
                pos1 = temp.find("fill-opacity") + 14;
                pos2 = temp.find("\"", pos1);
                fill_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                fill_opacity = 1;
            }

            double stroke_opacity;
            if (temp.find("stroke-opacity") < temp.size())
            {
                pos1 = temp.find("stroke-opacity=") + 16;
                pos2 = temp.find("\"", pos1);
                stroke_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                stroke_opacity = 1;
            }
            string points;
            Point2D* pointsArray = NULL;
            int NumOfPoint = 0;
            vector<Point2D> pointArray;
            if (temp.find("points=") < temp.size())
            {
                pos1 = temp.find("points=") + 8;
                pos2 = temp.find("\"", pos1);
                points = temp.substr(pos1, pos2 - pos1);
                stringstream ss(points);
                string point;

                while (getline(ss, point, ' ')) {
                    stringstream pointSS(point);
                    string coordinate;
                    vector<int> coordinates;

                    while (getline(pointSS, coordinate, ',')) {
                        coordinates.push_back(stoi(coordinate));
                    }

                    Point2D pointObj(coordinates[0], coordinates[1]);
                    pointArray.push_back(pointObj);
                }

                NumOfPoint = pointArray.size();
                pointsArray = new Point2D[NumOfPoint];
                for (int i = 0; i < NumOfPoint; i++)
                {
                    pointsArray[i] = pointArray[i];
                }
            }
            else
            {
                NumOfPoint = 0;
                Point2D* pointsArray = NULL;
            }
            PolyGon Polygon;
            Polygon.SetPolyGon(rgb, fill_rgb, thickness, NumOfPoint, pointsArray, fill_opacity, stroke_opacity);
            Polygon.fillPolygon(hdc);
            Polygon.OnPaint(hdc);

            delete[] pointsArray;
        }
        else if (temp.find("line") < temp.length())
        {
            //HDC hdc, int* rgb, Point2D start, Point2D end, int thickness, double stroke_opacity
            int pos1, pos2;
            int rgb[3];
            if (temp.find("stroke=") < temp.length())
            {
                pos1 = temp.find("stroke=") + 12;
                pos2 = temp.find(",", pos1);

                rgb[0] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(",", pos1);
                rgb[1] = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = pos2 + 1;
                pos2 = temp.find(")", pos1);
                rgb[2] = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                rgb[0] = rgb[1] = rgb[2] = 0;
            }
            Point2D start, end;
            int x, y;
            if (temp.find("x1=") < temp.length())
            {
                pos1 = temp.find("x1=") + 4;
                pos2 = temp.find("\"", pos1);
                x = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = temp.find("y1=") + 4;
                pos2 = temp.find("\"", pos1);
                y = stoi(temp.substr(pos1, pos2 - pos1));
                start.SetPoint(x, y);
            }
            else
            {
                start.SetPoint(0, 0);
            }

            if (temp.find("x2=") < temp.length())
            {
                pos1 = temp.find("x2=") + 4;
                pos2 = temp.find("\"", pos1);
                x = stoi(temp.substr(pos1, pos2 - pos1));

                pos1 = temp.find("y2=") + 4;
                pos2 = temp.find("\"", pos1);
                y = stoi(temp.substr(pos1, pos2 - pos1));
                end.SetPoint(x, y);
            }
            else
            {
                end.SetPoint(0, 0);
            }

            double stroke_opacity;
            if (temp.find("stroke-opacity") < temp.size())
            {
                pos1 = temp.find("stroke-opacity=") + 16;
                pos2 = temp.find("\"", pos1);
                stroke_opacity = stod(temp.substr(pos1, pos2 - pos1));
            }
            else
                stroke_opacity = 1;

            int thickness;
            if (temp.find("stroke-width") < temp.length())
            {
                pos1 = temp.find("stroke-width=") + 14;
                pos2 = temp.find("\"", pos1);
                thickness = stoi(temp.substr(pos1, pos2 - pos1));
            }
            else
            {
                thickness = 0;
            }

            Line line;
            line.SetLine(rgb, start, end, thickness, stroke_opacity);
            line.OnPaint(hdc);
        }
    }
    In.close();
}




VOID Shape::OnPaint(HDC hdc, double opacity) {}
void Shape::fillRect(HDC hdc, double fill_opacity) {}
void Shape::_fillCircle(HDC, double) {}
void Shape::fillPoline(HDC, double) {}
void Shape::fillPolygon(HDC, double) {}

Shape::~Shape() {
    delete[] ShapeArr;
}











VOID Example_DrawCurve2(HDC hdc)
{
    Graphics graphics(hdc);

    // Define a Pen object and an array of Point objects.
    Pen greenPen(Color::Green, 3);
    Point point1(100, 100);
    Point point2(200, 50);
    Point point3(400, 10);
    Point point4(500, 100);

    Point curvePoints[4] = {
    point1,
    point2,
    point3,
    point4 };

    Point* pcurvePoints = curvePoints;

    // Specify offset, number of segments to draw, and tension.
    int offset = 1;
    int segments = 2;
    REAL tension = 1.0;

    // Draw the curve.
    graphics.DrawCurve(&greenPen, curvePoints, 4, offset, segments, tension);

    //Draw the points in the curve.
    SolidBrush redBrush(Color::Red);
    graphics.FillEllipse(&redBrush, Rect(95, 95, 10, 10));
    graphics.FillEllipse(&redBrush, Rect(195, 45, 10, 10));
    graphics.FillEllipse(&redBrush, Rect(395, 5, 10, 10));
    graphics.FillEllipse(&redBrush, Rect(495, 95, 10, 10));
}







VOID Example_DrawPolygon(HDC hdc)
{
    Graphics graphics(hdc);


    // Create a Pen object.
    Pen blackPen(Color(255, 0, 0, 0), 3);

    // Create an array of Point objects that define the polygon.
    Point point1(100, 100);
    Point point2(200, 130);
    Point point3(150, 200);
    Point point4(50, 200);
    //Point point5(0, 130);
    Point points[5] = { point1, point2, point3, point4 };
    Point* pPoints = points;

    // Draw the polygon.
    graphics.DrawPolygon(&blackPen, pPoints, 4);
}

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
