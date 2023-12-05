#pragma once
#include "stdafx.h"
#include "rapidxml.hpp"
#include <vector>
#include <string>

using namespace std;

class Transform {
private:
	string name;
	int translate[2];
	int scale[2];
	int rotate[3];

public:
	void SetName(string name);
	string GetName();

	void SetTranslate(int, int);
	int* GetTranslate();

	void SetScale(int, int);
	int* GetScale();

	void SetRotate(int, int, int);
	int* GetRotate();
};