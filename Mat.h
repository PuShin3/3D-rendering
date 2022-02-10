#pragma once
#ifndef _MAT_H_
#define _MAT_H_
#include "Struct.h"
#include <math.h>

vec3d Vector_Add(vec3d& v1, vec3d& v2);

vec3d Vector_Sub(vec3d& v1, vec3d& v2);

vec3d Vector_Mul(vec3d& v1, float k);

vec3d Vector_Div(vec3d& v1, float k);

float Vector_DotProduct(vec3d& v1, vec3d& v2);

float Vector_Length(vec3d& v);

vec3d Vector_Normalise(vec3d& v);

vec3d Vector_CrossProduct(vec3d& v1, vec3d& v2);

vec3d MultiplyVector(mat4& m, vec3d& i);

mat4 MakeIdentity();

mat4 RotationX(float AngleRad);

mat4 RotationY(float AngleRad);

mat4 RotationZ(float AngleRad);

mat4 MakeTranslation(vec3d p);

mat4 MakeProjection(float FovDeg, float AspectRatio, float Near, float Far);

mat4 MultiplyMatrix(mat4& m1, mat4& m2);

mat4 Matrix_PointAt(vec3d& pos, vec3d& target, vec3d& up);

mat4 Matrix_QuickInverse(mat4& m);

vec3d IntersectPlane(vec3d& plane_p, vec3d& plane_n, vec3d& lineStart, vec3d& lineEnd);
#endif