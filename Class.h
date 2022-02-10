#pragma once
#ifndef _CLASS_H_
#define _CLASS_H_
#endif


#include "Mat.h"
#include "Init.h"
#include "Struct.h"

//#define wds 100
//#define scl 20;
//#define width 2000;
//#define height 40;

class Cam {
public:
	float y_movement = 0.0f;
	bool jumped = false;
	vec3d pos;
	vec3d rot;
	float fov;
	float speed;

	Cam(vec3d p, vec3d r, float f, float s);
	vec3d get3dcoord(vec3d p);

	vec3d get2dcoord(vec3d p);

	float distance(vec3d p1);
};

//struct Terrain {
//public:
//	std::vector<triangle> tris;
//	float t[wds][wds];
//
//	void make_value();
//
//	void triangle_strip(float points[wds][wds]);
//
//	void move_vertical(int n);
//
//	void move_horizontal(int n);
//
//private:
//	int primeIndex = 1;
//	int numX = 512;
//	int numY = 512;
//	int numOctaves = 5;
//
//	float persistence = 0.5;
//	int primes[10][3] = {
//	  { 995615039, 600173719, 701464987 },
//	  { 831731269, 162318869, 136250887 },
//	  { 174329291, 946737083, 245679977 },
//	  { 362489573, 795918041, 350777237 },
//	  { 457025711, 880830799, 909678923 },
//	  { 787070341, 177340217, 593320781 },
//	  { 405493717, 291031019, 391950901 },
//	  { 458904767, 676625681, 424452397 },
//	  { 531736441, 939683957, 810651871 },
//	  { 997169939, 842027887, 423882827 }
//	};
//
//	float Noise(int i, int x, int y);
//
//	float SmoothedNoise(int i, int x, int y);
//
//	float Interpolate(float a, float b, float x);
//
//	float InterpolatedNoise(int i, float x, float y);
//
//	float ValueNoise_2D(float x, float y);
//};
