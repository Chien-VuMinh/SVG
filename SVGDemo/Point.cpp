#include "stdafx.h"
#include "rapidxml.hpp"
#include "Point.h"


Point2D::Point2D() : x(0), y(0) {}


Point2D::Point2D(double x, double y) {
	this->x = x;
	this->y = y;
}


double Point2D::GetX() {
	return this->x;
}


double Point2D::GetY() {
	return this->y;
}


void Point2D::SetPoint(double x, double y) {
	this->x = x;
	this->y = y;
}


Point2D:: ~Point2D() {

}