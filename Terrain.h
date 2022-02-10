#pragma once
#ifndef _TERRAIN_H_
#define _TERRAIN_H_
#endif

#include <vector>
#include <unordered_map>
#include "Struct.h"
#include "Noise.h"

#define wds 150
#define scl 20
#define width 3000
#define height 120
#define Gscl 1

struct Terrain {
public:
	std::vector<triangle> tris;
	vec3d p = { -width / 2, 0.0f, -width / 2 };
	float h[wds][wds];

	std::unordered_map<std::pair<int, int>, float, pair_hash> queue;
	std::unordered_map<std::pair<int, int>, float, pair_hash> Extraheight;

	void make_value();

	void triangle_Strip();
};