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
#include "LinearGradient.h"



Shape::Shape() {}


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
    vector<LinearGradient> gradient;
    for (rapidxml::xml_node<>* node = root->first_node(); node; node = node->next_sibling()) {
        string name = node->name();


        if (name == "g") {
            double fill_opacity = 1, stroke_opacity = 1;
            int thickness = 0, font_size = 0;
            int fill[] = { 0, 0, 0 },
                stroke_fill[] = { 0,0,0 };
            vector<Transform> transform;

            for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                name = attr->name();
                string value = attr->value();

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

                else if (name == "font-size")
                    font_size = stoi(value);

                else if (name == "transform") {
                    readTransform(value, transform);
                }
            }
            for (rapidxml::xml_node<>* n = node->first_node(); n; n = n->next_sibling()) {
                Draw(hdc, n, fill, fill_opacity, stroke_fill, stroke_opacity, thickness, 
                    transform, gradient, font_size);
            }
            
        }

        else if (name == "defs") {
            double x1 = 0, y1 = 0, x2 = 1, y2 = 1;
            LinearGradient g;

            for (rapidxml::xml_node<>* attr = node->first_node(); attr; attr = attr->next_sibling()) {
                name = attr->name();
                if(name == "linearGradient") {
                    for (rapidxml::xml_attribute<>* n = attr->first_attribute(); n; n = n->next_attribute()) {
                        name = n->name();
                        string value = n->value();


                        if (name == "id")
                            g.id = value;

                        else if (name == "x1")
                            x1 = stof(value);

                        else if (name == "x2")
                            x2 = stof(value);

                        else if (name == "y1")
                            y1 = stof(value);

                        else if (name == "y2")
                            y2 = stof(value);
                    }
                    g.p1.SetPoint(x1, y1);
                    g.p2.SetPoint(x2, y2);

                    rapidxml::xml_node<>* n2 = attr->first_node();
                    for (rapidxml::xml_attribute<>* n = n2->first_attribute(); n; n = n->next_attribute()) {
                        name = n->name();
                        string value = n->value();

                        if (name == "stop-color")
                        {
                            readRGB(value, g.rgb1);
                        }
                    }
                    n2 = n2->next_sibling();
                    for (rapidxml::xml_attribute<>* n = n2->first_attribute(); n; n = n->next_attribute()) {
                        name = n->name();
                        string value = n->value();

                        if (name == "stop-color")
                        {
                            readRGB(value, g.rgb2);
                        }
                    }

                    gradient.push_back(g);
                }
            }
        }

        else {
            double fill_opacity = 1, stroke_opacity = 1;
            int thickness = 0, font_size = 0;
            int fill[] = { 0, 0, 0 },
                stroke_fill[] = { 0,0,0 };
            vector<Transform> transform;

            Draw(hdc, node, fill, fill_opacity, stroke_fill, stroke_opacity, thickness, 
                transform, gradient, font_size);
        }

    }
}


void Shape::readRGB(string value, int* rgb) {
    int color;
    if (value[0] == 'r' && value[1] == 'g' && value[2] == 'b') {
        int ind1, ind2;
        for (int i = 0; i < value.size(); ++i) 
            if (value[i] == '(')
                ind1 = i + 1;
        ind2 = value.find(",", ind1);
        color = stoi(value.substr(ind1, ind2 - ind1));
        rgb[0] =  color > 255 ? 255 : color;

        ind1 = ind2 + 1;
        ind2 = value.find(",", ind1);
        color = stoi(value.substr(ind1, ind2 - ind1));
        rgb[1] = color > 255 ? 255 : color;

        ind1 = ind2 + 1;
        ind2 = value.find(")", ind1);
        color = stoi(value.substr(ind1, ind2 - ind1));
        rgb[2] = color > 255 ? 255 : color;
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

    // ref: https://www.w3schools.com/css/css_colors_rgb.asp
    else {
        for (int i = 0; i < value.length(); i++) {
            if (value[i] >= 'A' && value[i] <= 'Z') {
                value[i] += 32;
            }
        }

        ifstream read("colors.txt");
        
        string s;
        while (!read.eof()) {
            getline(read, s);
            int ind1 = s.find("#") - 1, ind2;
            string color = s.substr(0, ind1);
            for (int i = 0; i < color.length(); i++) {
                if (color[i] >= 'A' && color[i] <= 'Z') {
                    color[i] += 32;
                }
            }

            if (color == value) {
                ind1 = s.find("(") + 1;
                ind2 = s.find(",");
                rgb[0] = stoi(s.substr(ind1, ind2 - ind1));

                ind1 = ind2 + 1;
                ind2 = s.find(",", ind1);
                rgb[1] = stoi(s.substr(ind1, ind2 - ind1));

                ind1 = ind2 + 1;
                ind2 = s.find(")");
                rgb[2] = stoi(s.substr(ind1, ind2 - ind1));
            }
        }

        read.close();
    }
}


void Shape::readTransform(string value, vector<Transform>& transform){
    for (int i = 0; i < value.size(); ++i) {
        if (value[i] == '\n' || value[i] == ',')
            value[i] = ' ';
    }

    Transform trans;

    for (int i = 0; i < value.size(); ++i) {
        if (value[i] == 't') {
            int x1 = 0, x2 = 0, x3 = 0;
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
            int x1 = 0, x2 = 0, x3 = 0;
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
            double x1 = 0, x2 = 0;
            trans.SetName("s");

            int ind1 = i + 6;
            int ind2;

            if (value.find(" ", ind1) < value.find(")", ind1)) {
                ind2 = value.find(" ", ind1);
                x1 = stod(value.substr(ind1, ind2 - ind1));


                ind1 = ind2 + 1;
                ind2 = value.find(")", ind1);
                x2 = stod(value.substr(ind1, ind2 - ind1));
            }
            else {
                ind2 = value.find(")", ind1);
                x1 = x2 = stod(value.substr(ind1, ind2 - ind1));
            }
            trans.SetScale(x1, x2);
            transform.push_back(trans);

            i = ind2 + 1;
        }
    }
}

void Shape::Draw(HDC hdc, xml_node<>*& root, int* fill, double fill_opacity, int* stroke_fill,
                 double stroke_opacity, int thickness, vector<Transform> transform, 
                 vector<LinearGradient> gradient, int font_size) {
    string name = root->name();
    double fill_opacity2 = fill_opacity, stroke_opacity2 = stroke_opacity;
    int thickness2 = thickness, font_size2 = font_size;
    int fill2[] = { 0, 0, 0 },
        stroke_fill2[] = { 0,0,0 };
    bool linearGradient = 0;
    LinearGradient Gradient;

    for (int i = 0; i < 3; ++i) {
        fill2[i] = fill[i];
        stroke_fill2[i] = stroke_fill[i];
    }

    if (name == "g") {
        vector<Transform> transform2;
        for (int i = 0; i < transform.size(); ++i)
            transform2.push_back(transform[i]);

        for (rapidxml::xml_attribute<>* attr = root->first_attribute(); attr; attr = attr->next_attribute()) {
            name = attr->name();
            string value = attr->value();
            if (name == "fill-opacity")
                fill_opacity2 = stod(value);

            else if (name == "stroke-opacity")
                stroke_opacity2 = stod(value);

            else if (name == "fill") {
                if (value == "none" || value == "transparent")
                    fill_opacity2 = 0;
                else
                    readRGB(value, fill2);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity2 = 0;
                else {
                    readRGB(value, stroke_fill2);
                    if (thickness2 == 0)
                        thickness2 = 1;
                }
            }

            else if (name == "stroke-width") {
                thickness2 = stoi(value);
            }

            else if (name == "font-size")
                font_size2 = stoi(value);

            else if (name == "transform") {
                readTransform(value, transform2);
            }
        }
        
        for (rapidxml::xml_node<>* n = root->first_node(); n; n = n->next_sibling()) {
            Draw(hdc, n, fill2, fill_opacity2, stroke_fill2, stroke_opacity2, thickness2, transform2, gradient, font_size2);
        }
    }

    else if (name == "rect") {
        int  width, height, x = 10, y = 10;
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
                    readRGB(value, fill2);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill2);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "style") {
                if (value.find("fill") < value.size()) {
                    int ind = value.find("fill") + 5;

                    if (value[ind] == 'u') {
                        ind += 5;
                        linearGradient = 1;
                        string id = value.substr(ind, value.find(")", ind) - ind);

                        for (int i = 0; i < gradient.size(); ++i) {
                            if (id == gradient[i].id) {
                                Gradient = gradient[i];
                            }
                        }
                    }

                    else {
                        string color = value.substr(ind, value.size() - ind);
                        if (value == "none" || value == "transparent")
                            fill_opacity = 0;
                        else
                            readRGB(color, fill2);
                    }
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
        Rec.SetRec(stroke_fill2, start, height, width, thickness, fill2, fill_opacity, stroke_opacity, transform);
        Rec.OnPaint(hdc);
        if (linearGradient) {
            Rec.myLinearGradientBrush(hdc, Gradient);
        }
    }

    else if (name == "circle" || name == "ellipse") {
        int  x = 0, y = 0, rx, ry = 0;
        Point2D start;

        for (rapidxml::xml_attribute<>* node = root->first_attribute(); node; node = node->next_attribute()) {
            name = node->name();
            string value = node->value();

            if (name == "fill-opacity")
                fill_opacity = stod(value);

            else if (name == "stroke-opacity")
                stroke_opacity = stod(value);

            else if (name == "style") {
                if (value.find("fill") < value.size()) {
                    int ind = value.find("fill") + 5;

                    if (value[ind] == 'u') {
                        ind += 5;
                        linearGradient = 1;
                        string id = value.substr(ind, value.find(")", ind) - ind);

                        for (int i = 0; i < gradient.size(); ++i) {
                            if (id == gradient[i].id) {
                                Gradient = gradient[i];
                            }
                        }
                    }

                    else {
                        string color = value.substr(ind, value.size() - ind);
                        if (value == "none" || value == "transparent")
                            fill_opacity = 0;
                        else
                            readRGB(color, fill2);
                    }
                }
            }

            else if (name == "fill") {
                if (value == "none" || value == "transparent")
                    fill_opacity = 0;
                else
                    readRGB(value, fill2);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill2);
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
        Cir.SetCircle(stroke_fill2, start, rx, ry, thickness, fill2, stroke_opacity, fill_opacity, transform);
        Cir.OnPaint(hdc);
        if (linearGradient) {
            Cir.myLinearGradientBrush(hdc, Gradient);
        }
    }

    else if (name == "text") {
        int x = 0, y = 0;
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
                    readRGB(value, fill2);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill2);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "x")
                x = stoi(value);

            else if (name == "y")
                y = stoi(value);

            else if (name == "font-size")
                font_size = stoi(value);

            else if (name == "stroke-width") {
                thickness = stoi(value);
            }

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }

        Text t;
        Point2D start(x, y);
        t.SetText(text, stroke_fill2, font_size, start, fill2, stroke_opacity, fill_opacity, thickness, transform);
        t.OnPaint(hdc);
    }

    else if (name == "polyline") {
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
                    readRGB(value, fill2);
            }

            else if (name == "style") {
                if (value.find("fill") < value.size()) {
                    int ind = value.find("fill") + 5;

                    if (value[ind] == 'u') {
                        ind += 5;
                        linearGradient = 1;
                        string id = value.substr(ind, value.find(")", ind) - ind);

                        for (int i = 0; i < gradient.size(); ++i) {
                            if (id == gradient[i].id) {
                                Gradient = gradient[i];
                            }
                        }
                    }

                    else {
                        string color = value.substr(ind, value.size() - ind);
                        if (value == "none" || value == "transparent")
                            fill_opacity = 0;
                        else
                            readRGB(color, fill2);
                    }
                }
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill2);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "points") {
                for (int i = 0; i < value.size(); ++i) {
                    if (value[i] == '\n' || value[i] == ',' || value[i] == 9) {
                        value[i] = ' ';
                    }
                }

                while (value[value.size() - 1] == ' ') {
                    value.erase(value.begin() + value.size() - 1);
                }

                for (int i = 0; i < value.size(); ++i) {
                    if ((i < value.size() - 1) && (value[i] == ' ' && value[i + 1] == ' ')) {
                        value.erase(value.begin() + i);
                        --i;
                    }
                }
                value += ' ';

                double x, y;
                int ind1 = 0, ind2;
                Point2D p;

                for (int j = 0; j < value.size(); ++j) {
                    if (value[j] == ' ') {
                        ind2 = j;
                        x = stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = stod(value.substr(ind1, ind2 - ind1));
                        ind1 = ind2 + 1;
                        j = ind2;

                        p.SetPoint(x, y);
                        pointArray.push_back(p);
                    }
                }
            }

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }
        
        PolyLine poly;
        poly.SetPolyLine(stroke_fill2, thickness, pointArray, fill2, fill_opacity, stroke_opacity, transform);
        poly.OnPaint(hdc);
        if (linearGradient) {
            poly.myLinearGradientBrush(hdc, Gradient); 
        }
    }

    else if (name == "polygon") {
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
                    readRGB(value, fill2);
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                    stroke_opacity = 0;
                else {
                    readRGB(value, stroke_fill2);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "style") {
                if (value.find("fill") < value.size()) {
                    int ind = value.find("fill") + 5;

                    if (value[ind] == 'u') {
                        ind += 5;
                        linearGradient = 1;
                        string id = value.substr(ind, value.find(")", ind) - ind);

                        for (int i = 0; i < gradient.size(); ++i) {
                            if (id == gradient[i].id) {
                                Gradient = gradient[i];
                            }
                        }
                    }

                    else {
                        string color = value.substr(ind, value.size() - ind);
                        if (value == "none" || value == "transparent")
                            fill_opacity = 0;
                        else
                            readRGB(color, fill2);
                    }
                }
            }

            else if (name == "stroke-width")
                thickness = stoi(value);

            else if (name == "points") {
                for (int i = 0; i < value.size(); ++i) {
                    if (value[i] == '\n' || value[i] == ',' || value[i] == 9) {
                        value[i] = ' ';
                    }
                }

                while (value[value.size() - 1] == ' ') {
                    value.erase(value.begin() + value.size() - 1);
                }

                for (int i = 0; i < value.size(); ++i) {
                    if ((i < value.size() - 1) && (value[i] == ' ' && value[i + 1] == ' ')) {
                        value.erase(value.begin() + i);
                        --i;
                    }
                }
                value += ' ';

                double x, y;
                int ind1 = 0, ind2;
                Point2D p;

                for (int j = 0; j < value.size(); ++j) {
                    if (value[j] == ' ') {
                        ind2 = j;
                        x = stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = stod(value.substr(ind1, ind2 - ind1));
                        ind1 = ind2 + 1;
                        j = ind2;

                        p.SetPoint(x, y);
                        pointArray.push_back(p);
                    }
                }
            }

            else if (name == "transform") {
                readTransform(value, transform);
            }
        }

        PolyGon poly;
        poly.SetPolyGon(stroke_fill2, fill2, thickness, pointArray, fill_opacity, stroke_opacity, transform);
        poly.OnPaint(hdc);
        if (linearGradient) { 
            poly.myLinearGradientBrush(hdc, Gradient);
        }
    }

    else if (name == "line") {
        int  x1, y1, x2, y2;
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
                    readRGB(value, stroke_fill2);
                    if (thickness == 0)
                        thickness = 1;
                }
            }

            else if (name == "style") {
                if (value.find("fill") < value.size()) {
                    int ind = value.find("fill") + 5;

                    if (value[ind] == 'u') {
                        ind += 5;
                        linearGradient = 1;
                        string id = value.substr(ind, value.find(")", ind) - ind);

                        for (int i = 0; i < gradient.size(); ++i) {
                            if (id == gradient[i].id) {
                                Gradient = gradient[i];
                            }
                        }
                    }

                    else {
                        string color = value.substr(ind, value.size() - ind);
                        if (value == "none" || value == "transparent")
                            fill_opacity = 0;
                        else
                            readRGB(color, fill2);
                    }
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
        line.SetLine(stroke_fill2, p1, p2, thickness, stroke_opacity, transform);
        line.OnPaint(hdc);
        if (linearGradient) {
            line.myLinearGradientBrush(hdc, Gradient);
        }
    }

    else if (name == "path") {
        Point2D start;

        vector<vector<vector<Point2D>>> MultiPath;
        vector<vector<Point2D>> points;

        vector<vector<char>> Commands;
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

            else if (name == "style") {
                if (value.find("fill") < value.size()) {
                    int ind = value.find("fill") + 5;

                    if (value[ind] == 'u') {
                        ind += 5;
                        linearGradient = 1;
                        string id = value.substr(ind, value.find(")", ind) - ind);

                        for (int i = 0; i < gradient.size(); ++i) {
                            if (id == gradient[i].id) {
                                Gradient = gradient[i];
                            }
                        }
                    }

                    else {
                        string color = value.substr(ind, value.size() - ind);
                        if (value == "none" || value == "transparent")
                            fill_opacity = 0;
                        else
                            readRGB(color, fill2);
                    }
                }
            }

            else if (name == "fill") {
                if (value == "none" || value == "transparent") {
                    fill_opacity = 0;
                }
                else
                {
                    readRGB(value, fill2);
                }
            }

            else if (name == "stroke") {
                if (value == "none" || value == "transparent")
                {
                    stroke_opacity = 0;
                }
                else {
                    readRGB(value, stroke_fill2);
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
                    if (value[i] == '\n' || value[i] == ',' || value[i] == 9) {
                        value[i] = ' ';
                    }
                }

                for (int i = 0; i < value.size(); ++i) {
                    if ((value[i] >= 'A' && value[i] <= 'Z') || (value[i] >= 'a' && value[i] <= 'z')) {
                        if (i > 1 && value[i - 1] != ' ')
                            value.insert(i, " ");
                    }

                    else if (value[i] == '-') {
                        if (value[i - 1] >= '0' && value[i - 1] <= '9')
                            value.insert(i, " ");
                    }

                    else if ((i < value.size() - 1) && (value[i] == ' ' && value[i + 1] == ' ')) {
                        value.erase(value.begin() + i);
                        --i;
                    }
                }
                value += ' ';
                
                for (int i = 0; i < value.size() - 1; ++i) {
                    if (value[i] == '.') {
                        int k = 0;
                        for (int j = i + 1; j < value.size(); ++j) {
                            if (value[j] == '.')
                                k = j;

                            else if (value[j] == ' ' && k == 0)
                                break;

                            else if (value[j] == ' ' && k != 0) {
                                value.insert(k, " ");
                                break;
                            }
                        }
                    }
                }

                double x = 0, y = 0;

                for (int i = 0; i < value.size(); ++i) {

                    if (value[i] == 'm') {
                        int ind1, ind2;

                        ind1 = i + 1;
                        ind2 = value.find(" ", ind1);
                        x = startP.GetX() + stod(value.substr(ind1, ind2 - ind1));


                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = startP.GetY() + stod(value.substr(ind1, ind2 - ind1));

                        startP.SetPoint(x, y);

                        i = ind2;

                        InitialP = startP;

                        if (value[i + 1] >= '0' && value[i + 1] <= '9') {
                            command.push_back('m');

                            vector<Point2D> Parray;
                            Parray.push_back(startP);

                            ind1 = ind2 + 1;
                            ind2 = value.find(" ", ind1);
                            x = startP.GetX() + stod(value.substr(ind1, ind2 - ind1));

                            ind1 = ind2 + 1;
                            ind2 = value.find(" ", ind1);
                            y = startP.GetY() + stod(value.substr(ind1, ind2 - ind1));

                            startP.SetPoint(x, y);
                            Parray.push_back(startP);

                            points.push_back(Parray);
                            i = ind2;
                        }
                    }

                    else if (value[i] == 'M') {
                        int ind1, ind2;

                        ind1 = i + 1;
                        ind2 = value.find(" ", ind1);
                        x = stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = stod(value.substr(ind1, ind2 - ind1));
                        startP.SetPoint(x, y);

                        i = ind2;

                        InitialP = startP;

                        if (value[i + 1] >= '0' && value[i + 1] <= '9') {
                            command.push_back('m');

                            vector<Point2D> Parray;
                            Parray.push_back(startP);

                            ind1 = ind2 + 1;
                            ind2 = value.find(" ", ind1);
                            x = stod(value.substr(ind1, ind2 - ind1));

                            ind1 = ind2 + 1;
                            ind2 = value.find(" ", ind1);
                            y = stod(value.substr(ind1, ind2 - ind1));

                            startP.SetPoint(x, y);
                            Parray.push_back(startP);

                            points.push_back(Parray);
                            i = ind2;
                        }
                    }

                    else if (value[i] == 'c') {
                        command.push_back('c');

                        int ind1 = i + 1, ind2;
                        Point2D p;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        for (int j = ind1; j < value.size(); ++j) {
                            if (value[j] < 65 || (value[j] > 90 && value[j] < 97) || value[j] > 122) {
                                if (value[j] == ' ') {
                                    ind2 = j;

                                    x = startP.GetX() + stod(value.substr(ind1, ind2 - ind1));
                                    ind1 = ind2 + 1;
                                    ind2 = value.find(" ", ind1);

                                    y = startP.GetY() + stod(value.substr(ind1, ind2 - ind1));
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

                        int ind1 = i + 1, ind2;
                        Point2D p;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        for (int j = ind1; j < value.size(); ++j) {
                            if (value[j] < 65 || (value[j] > 90 && value[j] < 97) || value[j] > 122) {
                                if (value[j] == ' ') {
                                    ind2 = j;

                                    x = stod(value.substr(ind1, ind2 - ind1));
                                    ind1 = ind2 + 1;
                                    ind2 = value.find(" ", ind1);

                                    y = stod(value.substr(ind1, ind2 - ind1));
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
                    
                    else if (value[i] == 's') {
                        command.push_back('s');

                        int ind1 = i + 1, ind2;
                        double x1, x2, y1, y2;
                        Point2D p;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        ind2 = value.find(" ", ind1);
                        x1   = startP.GetX() + stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y1   = startP.GetY() + stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        x2   = startP.GetX() + stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y2   = startP.GetY() + stod(value.substr(ind1, ind2 - ind1));

                        p.SetPoint(x1 - x2 + startP.GetX(), y1 - y2 + startP.GetY());
                        Parray.push_back(p);

                        p.SetPoint(x1, y1);
                        Parray.push_back(p);

                        p.SetPoint(x2, y2);
                        Parray.push_back(p);

                        points.push_back(Parray);
                        startP = p;
                        i = ind2;
                    }

                    else if (value[i] == 'S') {
                        command.push_back('S');

                        int ind1 = i + 1, ind2;
                        double x1, x2, y1, y2;
                        Point2D p;
                        vector<Point2D> Parray;
                        Parray.push_back(startP);

                        ind2 = value.find(" ", ind1);
                        x1 = stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y1 = stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        x2 = stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y2 = stod(value.substr(ind1, ind2 - ind1));

                        p.SetPoint(x1 - x2 + startP.GetX(), y1 - y2 + startP.GetY());
                        Parray.push_back(p);

                        p.SetPoint(x1, y1);
                        Parray.push_back(p);

                        p.SetPoint(x2, y2);
                        Parray.push_back(p);

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

                        x = startP.GetX() + stod(value.substr(ind1, ind2 - ind1));
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
                        x = stod(value.substr(ind1, ind2 - ind1));
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

                    y = startP.GetY() + stod(value.substr(ind1, ind2 - ind1));
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

                    y = stod(value.substr(ind1, ind2 - ind1));
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
                        x = startP.GetX() + stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = startP.GetY() + stod(value.substr(ind1, ind2 - ind1));

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
                        x = stod(value.substr(ind1, ind2 - ind1));

                        ind1 = ind2 + 1;
                        ind2 = value.find(" ", ind1);
                        y = stod(value.substr(ind1, ind2 - ind1));

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

                        startP = InitialP;
                        MultiPath.push_back(points);
                        Commands.push_back(command);
                        command.clear();
                        points.clear();
                    }
                }


            }
        }
        
        Path p;
        for (int i = 0; i < MultiPath.size(); ++i) {
            p.SetPath(stroke_fill2, fill2, thickness, Commands[i], MultiPath[i], fill_opacity, stroke_opacity, transform);
            p.OnPaint(hdc);
            if (linearGradient) {
                p.myLinearGradientBrush(hdc, Gradient);
            }
        }

        //p.SetPath(stroke_fill2, fill2, thickness, command, points, fill_opacity, stroke_opacity);
        //p.OnPaint(hdc, transform);
    }
}


VOID Shape::OnPaint(HDC hdc) {}

Shape::~Shape() {}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    Shape        shape;
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        shape.ReadSVGFile(hdc, "tiktok.svg");
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
