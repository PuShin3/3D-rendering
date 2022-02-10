#pragma once
#ifndef _3D_ENGINE_H_
#define _3D_ENGINE_H_
#endif
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <sstream>
#include <list>
#include "Struct.h"
#include "Class.h"
#include "Init.h"
#include "Mat.h"
#include "Noise.h"
#include "Terrain.h"


#define endl "\n"

float sign(vec3d p1, vec3d p2, vec3d p3);

bool PointInTriangle(vec3d pt, vec3d v1, vec3d v2, vec3d v3);

void draw_triangle(vec3d p1, vec3d p2, vec3d p3, int color[]);

void draw_line(vec3d p1, vec3d p2);
