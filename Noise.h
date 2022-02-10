#pragma once
#ifndef _NOISE_H_
#define _NOISE_H_
extern int primeIndex;
extern int	numOctaves;

extern double persistence;
extern int primes[10][3];
#endif
#include <math.h>

float Noise(int i, int x, int y);

float SmoothedNoise(int i, int x, int y);

float Interpolate(float a, float b, float x);

float InterpolatedNoise(int i, float x, float y);

float noise(float x, float y);