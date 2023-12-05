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
#include "Path.h"
#include <vector>
#include "Transform.h"



Shape::Shape() {
    ShapeArrSize = 0;
    ShapeArr = NULL;
}


void Shape::ReadSVGFile(HDC hdc, string file_name) {
    ifstream read(file_name);

    if (!read.is_open()) {
        cerr << "Không thể mở tệp " << file_name << endl;
    }
    // Đọc nội dung của tệp vào một vector<char>
    vector<char> buffer((istreambuf_iterator<char>(read)), istreambuf_iterator<char>());
    buffer.push_back('\0'); // Thêm ký tự kết thúc chuỗi

    // Khai báo một tài liệu XML để lưu trữ cấu trúc tệp SVG
    rapidxml::xml_document<> doc;

    // Phân tích nội dung tệp vào tài liệu XML
    doc.parse<0>(&buffer[0]);

    // Lấy nút gốc (root node) của tài liệu
    rapidxml::xml_node<>* root = doc.first_node("svg");

    read.close();

    HanleSVG(hdc, root);
}


void Shape::HanleSVG(HDC hdc, xml_node<>*& root) {
    for (rapidxml::xml_node<>* node = root->first_node(); node; node = node->next_sibling()) {
        string name = node->name();
        double fill_opacity = 1, stroke_opacity = 1;
        int rotate = 0;
        int translate[] = { 0, 0 },
            scale[] = { 0, 0 },
            fill[] = { 0, 0, 0 },
            stroke_fill[] = { 0,0,0 };
        vector<Transform> transform;

        if (name == "g") {
            for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {

            }
            Draw(hdc, node, fill, fill_opacity, stroke_fill, stroke_opacity, transform);
        }
        else {
            Draw(hdc, node, fill, fill_opacity, stroke_fill, stroke_opacity, transform);
        }

    }
}


void Shape::readRGB(string value, int*& rgb) {
    if (value[0] == 'r' && value[1] == 'g' && value[2] == 'b') {
        int ind1, ind2;
        for (int i = 0; i < value.size(); ++i) 
            if (value[i] == '(')
                ind1 = i + 1;
        ind2 = value.find(",", ind1);
        rgb[0] = stoi(value.substr(ind1, ind2 - ind1));

        ind1 = ind2 + 1;
        ind2 = value.find(",", ind1);
        rgb[1] = stoi(value.substr(ind1, ind2 - ind1));

        ind1 = ind2 + 1;
        ind2 = value.find(")", ind1);
        rgb[2] = stoi(value.substr(ind1, ind2 - ind1));
    }
    else if (value[0] == '#') {
        unsigned int hexValue;
        if (value.length() == 4) {
            char a1 = value[1], a2 = value[2], a3 = value[3];
            value = "#" + string(1, a1) + string(1, a1) + string(1, a2) + string(1, a2) + string(1, a3) + string(1, a3);
        }
        istringstream(value.substr(1)) >> hex >> hexValue;

        rgb[0] = (hexValue >> 16) & 0xFF;
        rgb[1] = (hexValue >> 8) & 0xFF;
        rgb[2] = hexValue & 0xFF;
        int alpha = (hexValue >> 24) & 0xFF;
    }
}

void Shape::GetP(vector<vector<Point2D>>& points, string s, int& n, Point2D startP) {
    int x, y, ind1 = n + 1, ind2;
    Point2D p;
    vector<Point2D> Parray;
    Parray.push_back(startP);

    for (int i = ind1; i < s.size(); ++i) {
        if (s[i] < 65 || (s[i] > 90 && s[i] < 97) || s[i] > 122) {
            if (s[i] == ' ') {
                ind2 = i;
                x = stoi(s.substr(ind1, ind2 - ind1));

                ind1 = ind2 + 1;
                ind2 = s.find(" ", ind1);
                y = stoi(s.substr(ind1, ind2 - ind1));

                ind1 = ind2 + 1;
                i = ind2;
                n = ind2;

                p.SetPoint(x, y);
                Parray.push_back(p);
            }
        }
        else
        {
            break;
        }
    }
    points.push_back(Parray);
}


void Shape::readTransform(string value, vector<Transform>& transform){
    for (int i = 0; i < value.size(); ++i) {
        if (value[i] == '\n' || value[i] == ',')
            value[i] = ' ';
    }

    Transform trans;
    int x1 = 0, x2 = 0, x3 = 0;

    for (int i = 0; i < value.size(); ++i) {
        if (value[i] == 't') {
            trans.SetName("t");

            int ind1 = i + 10;
            int ind2;

            if (value.find(" ", ind1) < value.find(")", ind1)) {
                ind2 = value.find(" ", ind1);
                x1 = stoi(value.substr(ind1, ind2 - ind1));


                ind1 = ind2 + 1;
                ind2 = value.find(")", ind1);
                x2 = stoi(value.substr(ind1, ind2 - ind1));
            }
            else {
                ind2 = value.find(")", ind1);
                x1 = stoi(value.substr(ind1, ind2 - ind1));
                x2 = 0;
            }
            trans.SetTranslate(x1, x2);
            transform.push_back(trans);

            i = ind2 + 1;
        }

        else if (value[i] == 'r') {
            trans.SetName("r");

            int ind1 = i + 7;
            int ind2;

            if (value.find(" ", ind1) < value.find(")", ind1)) {
                ind2 = value.find(" ", ind1);
                x1 = stoi(value.substr(ind1, ind2 - ind1));
                ind1 = ind2 + 1;

                if (value.find(" ", ind1) < value.find(")", ind1)) {
                    ind2 = value.find(" ", ind1);
                    x2 = stoi(value.substr(ind1, ind2 - ind1));
                    ind1 = ind2 + 1;

                    ind2 = value.find(")", ind1);
                    x3 = stoi(value.substr(ind1, ind2 - ind1));
                }
                else {
                    ind2 = value.find(")", ind1);
                    x2 = stoi(value.substr(ind1, ind2 - ind1));
                }
            }
            else {
                ind2 = value.find(")", ind1);
                x1 = stoi(value.substr(ind1, ind2 - ind1));
                x2 = 0;
            }


            trans.SetRotate(x1, x2, x3);
            transform.push_back(trans);

            i = ind2 + 1;
        }

        else if (value[i] == 's') {
            trans.SetName("s");

            int ind1 = i + 6;
            int ind2;

            if (value.find(" ", ind1) < value.find(")", ind1)) {
                ind2 = value.find(" ", ind1);
                x1 = stoi(value.substr(ind1, ind2 - ind1));


                ind1 = ind2 + 1;
                ind2 = value.find(")", ind1);
                x2 = stoi(value.substr(ind1, ind2 - ind1));
            }
            else {
                ind2 = value.find(")", ind1);
                x1 = x2 = stoi(value.substr(ind1, ind2 - ind1));
            }
            trans.SetScale(x1, x2);
            transform.push_back(trans);

            i = ind2 + 1;
        }
    }
}

void Shape::Draw(HDC hdc, xml_node<>*& root, int* fill, double fill_opacity, int* stroke_fill,
                 double stroke_opacity, vector<Transform>& transform) {
    string name = root->name();

    if (name == "rect") {
        int thickness = 0, width, height, x, y;
        Point2D start;

        for (rapidxml::xml_attribute<>* node = root->first_attribute(); node; node = node->next_attribute()) {
            name = node->name();
            string value = node->value();

            if (name == "fill-opacity")
                fill_opacity = stod(value);

            else if (name == "stroke-opacity")
                stroke_opacity = stod(value);

            else if (name == "fill") {
                if (value == "none" || value == "transparent")
                    fill_opacity = 0;
                else
                    readRGB(value, fill);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "stroke-width") {
                thickness = stoi(value);
            }

            else if (name == "x")
                x = stoi(value);

            else if (name == "y")
                y = stoi(value);

            else if (name == "width") {
                if (value[value.length() - 1] == 't')
                    value = value.substr(0, value.length() - 2);
                width = stoi(value);
            }

            else if (name == "height") {
                if (value[value.length() - 1] == 't')
                    value = value.substr(0, value.length() - 2);
                height = stoi(value);
            }

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }

        _Rectangle Rec;
        start.SetPoint(x, y);
        Rec.SetRec(stroke_fill, start, height, width, thickness, fill, fill_opacity, stroke_opacity);
        Rec.OnPaint(hdc, transform);
    }

    else if (name == "circle" || name == "ellipse") {
        int thickness = 0, x, y, rx, ry = 0;
        Point2D start;

        for (rapidxml::xml_attribute<>* node = root->first_attribute(); node; node = node->next_attribute()) {
            name = node->name();
            string value = node->value();

            if (name == "fill-opacity")
                fill_opacity = stod(value);

            else if (name == "stroke-opacity")
                stroke_opacity = stod(value);

            else if (name == "fill") {
                if (value == "none" || value == "transparent")
                    fill_opacity = 0;
                else
                    readRGB(value, fill);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "stroke-width") {
                thickness = stoi(value);
            }

            else if (name == "cx")
                x = stoi(value);

            else if (name == "cy")
                y = stoi(value);

            else if (name == "r" || name == "rx")
                rx = ry = stoi(value);

            else if (name == "ry")
                ry = stoi(value);

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }

        Circle Cir;
        start.SetPoint(x, y);
        Cir.SetCircle(stroke_fill, start, rx, ry, thickness, fill, stroke_opacity, fill_opacity);
        Cir.OnPaint(hdc, transform);
    }

    else if (name == "text") {
        int x, y, font_size = 10;
        string text = root->value();

        for (rapidxml::xml_attribute<>* node = root->first_attribute(); node; node = node->next_attribute()) {
            name = node->name();
            string value = node->value();

            if (name == "fill-opacity")
                fill_opacity = stod(value);

            else if (name == "stroke-opacity")
                stroke_opacity = stod(value);

            else if (name == "fill") {
                if (value == "none" || value == "transparent")
                    fill_opacity = 0;
                else
                    readRGB(value, fill);
            }

            else if (name == "x")
                x = stoi(value);

            else if (name == "y")
                y = stoi(value);

            else if (name == "font-size")
                font_size = stoi(value);

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }

        Text t;
        Point2D start(x, y);
        t.SetText(text, fill, font_size, start);
        t.OnPaint(hdc, transform);
    }

    else if (name == "polyline") {
        int thickness = 0;
        vector<Point2D> pointArray;

        for (rapidxml::xml_attribute<>* node = root->first_attribute(); node; node = node->next_attribute()) {
            name = node->name();
            string value = node->value();

            if (name == "fill-opacity")
                fill_opacity = stod(value);

            else if (name == "stroke-opacity")
                stroke_opacity = stod(value);

            else if (name == "fill") {
                if (value == "none" || value == "transparent")
                    fill_opacity = 0;
                else
                    readRGB(value, fill);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "points") {
                string points;
                int NumOfPoint = 0;
                Point2D* pointsArray = NULL;
                int pos1 = 0;
                int pos2 = value.size();
                points = value.substr(pos1, pos2 - pos1);

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
            }

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }
        
        PolyLine poly;
        poly.SetPolyLine(stroke_fill, thickness, pointArray, fill, fill_opacity, stroke_opacity);
        poly.OnPaint(hdc, transform);
    }

    else if (name == "polygon") {
        int thickness = 0;
        vector<Point2D> pointArray;

        for (rapidxml::xml_attribute<>* node = root->first_attribute(); node; node = node->next_attribute()) {
            name = node->name();
            string value = node->value();

            if (name == "fill-opacity")
                fill_opacity = stod(value);

            else if (name == "stroke-opacity")
                stroke_opacity = stod(value);

            else if (name == "fill") {
                if (value == "none" || value == "transparent")
                    fill_opacity = 0;
                else
                    readRGB(value, fill);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "stroke-width")
                thickness = stoi(value);

            else if (name == "points") {
                string points;
                int NumOfPoint = 0;
                Point2D* pointsArray = NULL;
                int pos1 = 0;
                int pos2 = value.size();
                points = value.substr(pos1, pos2 - pos1);

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
            }

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }

        PolyGon poly;
        poly.SetPolyGon(stroke_fill, fill, thickness, pointArray, fill_opacity, stroke_opacity);
        poly.OnPaint(hdc, transform);
    }

    else if (name == "line") {
        int thickness = 0, x1, y1, x2, y2;
        Point2D start;

        for (rapidxml::xml_attribute<>* node = root->first_attribute(); node; node = node->next_attribute()) {
            name = node->name();
            string value = node->value();

            if (name == "stroke-opacity")
                stroke_opacity = stod(value);

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "stroke-width") {
                thickness = stoi(value);
            }

            else if (name == "x1")
                x1 = stoi(value);

            else if (name == "y1")
                y1 = stoi(value);

            else if (name == "x2")
                x2 = stoi(value);

            else if (name == "y2")
                y2 = stoi(value);

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }

        Line line;
        Point2D p1(x1, y1), p2(x2, y2);
        line.SetLine(stroke_fill, p1, p2, thickness, stroke_opacity);
        line.OnPaint(hdc, transform);
    }

    else if (name == "path") {
        int thickness = 0;
        Point2D start;

        vector<vector<Point2D>> points;
        vector<char> command;

        Point2D InitialP(0, 0);
        Point2D startP(0, 0);

        for (rapidxml::xml_attribute<>* node = root->first_attribute(); node; node = node->next_attribute()) {
            name = node->name();
            string value = node->value();

            if (name == "stroke-opacity")
            {
                stroke_opacity = stod(value);
            }

            else if (name == "fill-opacity")
            {
                fill_opacity = stod(value);
            }

            else if (name == "fill") {
                if (value == "none" || value == "transparent") {
                    fill_opacity = 0;
                }
                else
                {
                    readRGB(value, fill);
                }
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                {
                    stroke_opacity = 0;
                }
                else {
                    readRGB(value, stroke_fill);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "stroke-width") {
                thickness = stoi(value);
            }

            else if (name == "transform") {
                readTransform(value, transform);
            }

            else if (name == "d") {
                for (int i = 0; i < value.size(); ++i) {
                    if (value[i] == '\n' || value[i] == ',')
                        value[i] = ' ';
                }
                value += ' ';

                int x = 0, y = 0;

                bool flag = 0;

                for (int i = 0; i < value.size(); ++i) {

                    if (value[i] == 'm') {
                        int ind1, ind2;

                        ind1 = i + 1;
                        ind2 = value.find(" ", ind1);
                        x += stoi(value.substr(ind1, ind2 - ind1));


                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y += stoi(value.substr(ind1, ind2 - ind1));

                        startP.SetPoint(x, y);

                        i = ind2;

                        startP.SetPoint(x, y);
                        if (flag == 0)
                        {
                            InitialP = startP;
                            flag = 1;
                        }
                    }

                    else if (value[i] == 'M') {
                        int ind1, ind2;

                        ind1 = i + 1;
                        ind2 = value.find(" ", ind1);
                        x = stoi(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = stoi(value.substr(ind1, ind2 - ind1));
                        startP.SetPoint(x, y);

                        i = ind2;

                        startP.SetPoint(x, y);
                        if (flag == 0)
                        {
                            InitialP = startP;
                            flag = 1;
                        }
                    }

                    else if (value[i] == 'c') {
                        command.push_back('c');

                        int x, y, ind1 = i + 1, ind2;
                        Point2D p;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        for (int j = ind1; j < value.size(); ++j) {
                            if (value[j] < 65 || (value[j] > 90 && value[j] < 97) || value[j] > 122) {
                                if (value[j] == ' ') {
                                    ind2 = j;

                                    x = startP.GetX() + stoi(value.substr(ind1, ind2 - ind1));
                                    ind1 = ind2 + 1;
                                    ind2 = value.find(" ", ind1);

                                    y = startP.GetY() + stoi(value.substr(ind1, ind2 - ind1));
                                    ind1 = ind2 + 1;
                                    while (value[ind1] == ' ') {
                                        ++ind1;
                                        ++ind2;
                                    }
                                    j = ind2;

                                    p.SetPoint(x, y);
                                    Parray.push_back(p);
                                }
                            }
                            else
                            {
                                break;
                            }
                        }

                        points.push_back(Parray);
                        startP = p;

                        i = ind2;
                    }

                    else if (value[i] == 'C') {
                        command.push_back('C');
                        int x, y, ind1 = i + 1, ind2;
                        Point2D p;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        for (int j = ind1; j < value.size(); ++j) {
                            if (value[j] < 65 || (value[j] > 90 && value[j] < 97) || value[j] > 122) {
                                if (value[j] == ' ') {
                                    ind2 = j;

                                    x = stoi(value.substr(ind1, ind2 - ind1));
                                    ind1 = ind2 + 1;
                                    ind2 = value.find(" ", ind1);

                                    y = stoi(value.substr(ind1, ind2 - ind1));
                                    ind1 = ind2 + 1;
                                    while (value[ind1] == ' ') {
                                        ++ind1;
                                        ++ind2;
                                    }
                                    j = ind2;

                                    p.SetPoint(x, y);
                                    Parray.push_back(p);
                                }
                            }
                            else
                            {
                                break;
                            }
                        }

                        points.push_back(Parray);
                        startP = p;
                        i = ind2;
                    }

                    else if (value[i] == 'h') {
                        command.push_back('h');
                        int ind1, ind2;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        ind1 = i + 1;
                        ind2 = value.find(" ", ind1);

                        x = startP.GetX() + stoi(value.substr(ind1, ind2 - ind1));
                        startP.SetPoint(x, startP.GetY());
                        Parray.push_back(startP);
                        points.push_back(Parray);

                        i = ind2;
                    }

                    else if (value[i] == 'H') {
                        command.push_back('H');
                        int ind1, ind2;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        ind1 = i + 1;
                        ind2 = value.find(" ", ind1);

                        x = stoi(value.substr(ind1, ind2 - ind1));
                        startP.SetPoint(x, startP.GetY());
                        Parray.push_back(startP);
                        points.push_back(Parray);

                        i = ind2;
                    }

                    else if (value[i] == 'v') {
                    command.push_back('v');
                    int ind1, ind2;
                    vector<Point2D> Parray;
                    Parray.push_back(startP);

                    ind1 = i + 1;
                    ind2 = value.find(" ", ind1);

                    y = startP.GetX() + stoi(value.substr(ind1, ind2 - ind1));
                    startP.SetPoint(startP.GetX(), y);
                    Parray.push_back(startP);
                    points.push_back(Parray);

                    i = ind2;
                    }

                    else if (value[i] == 'V') {
                    command.push_back('V');
                    int ind1, ind2;
                    vector<Point2D> Parray;
                    Parray.push_back(startP);

                    ind1 = i + 1;
                    ind2 = value.find(" ", ind1);

                    y = stoi(value.substr(ind1, ind2 - ind1));
                    startP.SetPoint(startP.GetX(), y);
                    Parray.push_back(startP);
                    points.push_back(Parray);

                    i = ind2;
                    }
                   
                    else if (value[i] == 'l') {
                        command.push_back('l');
                        int ind1, ind2;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        ind1 = i + 1;
                        ind2 = value.find(" ", ind1);
                        x = startP.GetX() + stoi(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = startP.GetY() + stoi(value.substr(ind1, ind2 - ind1));

                        startP.SetPoint(x, y);
                        Parray.push_back(startP);
                        points.push_back(Parray);

                        i = ind2;
                    }

                    else if (value[i] == 'L') {
                        command.push_back('L');
                        int ind1, ind2;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        ind1 = i + 1;
                        ind2 = value.find(" ", ind1);
                        x = stoi(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = stoi(value.substr(ind1, ind2 - ind1));

                        startP.SetPoint(x, y);
                        Parray.push_back(startP);
                        points.push_back(Parray);

                        i = ind2;
                    }
                    
                    else if (value[i] == 'Z' || value[i] == 'z') {
                        command.push_back('z');
                        vector<Point2D> Parray;
                        Parray.push_back(startP);
                        Parray.push_back(InitialP);
                        points.push_back(Parray);
                    }
                }


            }

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }
        
        Path p;
        p.SetPath(stroke_fill, fill, thickness, command, points, fill_opacity, stroke_opacity);
        p.OnPaint(hdc, transform);
    }
}


VOID Shape::OnPaint(HDC hdc, vector<Transform> transform) {}

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







VOID Example_DrawPath(HDC hdc)
{
    Graphics graphics(hdc);
    GraphicsPath myGraphicsPath;
    Pen myPen(Color(255, 0, 0));
    SolidBrush redBrush(Color( 0, 255, 0));
    myGraphicsPath.AddLine(0, 0, 30, 20);
    myGraphicsPath.AddEllipse(20, 20, 20, 40);
    myGraphicsPath.AddBezier(30, 60, 70, 60, 50, 30, 100, 10);
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);
    graphics.DrawPath(&myPen, &myGraphicsPath);
    graphics.FillPath(&redBrush, &myGraphicsPath);
}


VOID Example_DrawBeziers2(HDC hdc)
{
    Graphics graphics(hdc);

    // Define a Pen object and an array of PointF objects.
    Pen greenPen(Color(255, 0, 255, 0), 3);
    SolidBrush redBrush(Color(255, 255, 0, 0));
    PointF startPoint(100.0f, 100.0f);
    PointF ctrlPoint1(200.0f, 50.0f);
    PointF ctrlPoint2(400.0f, 10.0f);
    PointF endPoint1(500.0f, 100.0f);
    PointF ctrlPoint3(600.0f, 200.0f);
    PointF ctrlPoint4(700.0f, 400.0f);
    PointF endPoint2(500.0f, 500.0f);

    PointF curvePoints[7] = {
       startPoint,
       ctrlPoint1,
       ctrlPoint2,
       endPoint1,
       ctrlPoint3,
       ctrlPoint4,
       endPoint2 };


    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    GraphicsPath bezierPath;
    bezierPath.AddBeziers(curvePoints, 7);
    graphics.FillPath(&redBrush, &bezierPath);
    graphics.DrawPath(&greenPen, &bezierPath);
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Shape        shape;
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        shape.ReadSVGFile(hdc, "sample.svg");
        // Example_DrawPath(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
