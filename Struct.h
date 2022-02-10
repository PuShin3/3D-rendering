#pragma once
#ifndef _STRUCT_H_
#define _STRUCT_H_
#endif
#include <string>
#include <strstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <cstring>
#include <list>
#include "Init.h"
#include "Noise.h"

#define MAX_ERROR 100

struct vec3d {
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;
};

struct vec2d {
	float x = 0;
	float y = 0;
};

struct triangle {
	vec3d p[3];
	int color[3] = { 255, 255, 255 };
	vec3d normal;
	vec3d CamRay;
	float VDot;
	int TriangleIndex;
	vec3d TwoDp[3];
	float error;
};

struct mesh {
	std::vector<triangle> tris;
	std::vector<vec3d> verts;
	void getobj(std::string filename);
private:
	std::vector<std::string> split(const std::string& str, const std::string& pattern);
};

struct mat4 {
	float m[4][4] = { 0 };
};

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};