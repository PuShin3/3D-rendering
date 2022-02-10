#include "Mat.h"


vec3d Vector_Add(vec3d& v1, vec3d& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

vec3d Vector_Sub(vec3d& v1, vec3d& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

vec3d Vector_Mul(vec3d& v1, float k) {
	return { v1.x * k, v1.y * k, v1.z * k };
}

vec3d Vector_Div(vec3d& v1, float k) {
	return { v1.x / k, v1.y / k, v1.z / k };
}

float Vector_DotProduct(vec3d& v1, vec3d& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Vector_Length(vec3d& v) {
	return sqrtf(Vector_DotProduct(v, v));
}

vec3d Vector_Normalise(vec3d& v) {
	float l = Vector_Length(v);
	return { v.x / l, v.y / l, v.z / l };
}

vec3d Vector_CrossProduct(vec3d& v1, vec3d& v2) {
	vec3d v;
	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return v;
}

vec3d MultiplyVector(mat4& m, vec3d& i) {
	vec3d v;
	v.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
	v.x = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
	v.x = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
	v.x = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
	return v;
}

mat4 MakeIdentity() {
	mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

mat4 RotationX(float AngleRad) {
	mat4 matrix;
	matrix.m[0][0] = 1.0f;
	matrix.m[1][1] = cosf(AngleRad);
	matrix.m[1][2] = sinf(AngleRad);
	matrix.m[2][1] = -sinf(AngleRad);
	matrix.m[2][2] = cosf(AngleRad);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

mat4 RotationY(float AngleRad) {
	mat4 matrix;
	matrix.m[0][0] = cosf(AngleRad);
	matrix.m[0][2] = sinf(AngleRad);
	matrix.m[2][0] = -sinf(AngleRad);
	matrix.m[1][1] = 1.0f;
	matrix.m[2][2] = cosf(AngleRad);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

mat4 RotationZ(float AngleRad) {
	mat4 matrix;
	matrix.m[0][0] = cosf(AngleRad);
	matrix.m[0][1] = sinf(AngleRad);
	matrix.m[1][0] = -sinf(AngleRad);
	matrix.m[1][1] = cosf(AngleRad);
	matrix.m[2][2] = 1.0f;
	matrix.m[3][3] = 1.0f;
	return matrix;
}

mat4 MakeTranslation(vec3d p) {
	mat4 matrix = MakeIdentity();
	matrix.m[3][0] = p.x;
	matrix.m[3][1] = p.y;
	matrix.m[3][2] = p.z;
	return matrix;
}

mat4 MakeProjection(float FovDeg, float AspectRatio, float Near, float Far) {
	float FovRad = 1.0f / tan(FovDeg * 0.5f / 180.0f * 3.14159265f);
	mat4 matrix;
	matrix.m[0][0] = AspectRatio * FovRad;
	matrix.m[1][1] = FovRad;
	matrix.m[2][2] = Far / (Far - Near);
	matrix.m[3][2] = (-Far * Near) / (Far - Near);
	matrix.m[2][3] = 1.0f;
	matrix.m[3][3] = 0.0f;
	return matrix;
}

mat4 MultiplyMatrix(mat4& m1, mat4& m2) {
	mat4 matrix;
	for (int c = 0; c < 4; c++) {
		for (int r = 0; r < 4; r++) {
			matrix.m[r][c] = m1.m[r][0] * m2.m[0][c] + m1.m[r][1] * m2.m[1][c] + m1.m[r][2] * m2.m[2][c] + m1.m[r][3] * m2.m[3][c];
		}
	}
	return matrix;
}

mat4 Matrix_PointAt(vec3d& pos, vec3d& target, vec3d& up) {
	vec3d newForward = Vector_Sub(target, pos);
	newForward = Vector_Normalise(newForward);

	vec3d a = Vector_Mul(newForward, Vector_DotProduct(up, newForward));
	vec3d newUp = Vector_Sub(up, a);
	newUp = Vector_Normalise(newUp);

	vec3d newRight = Vector_CrossProduct(newUp, newForward);

	mat4 matrix;
	matrix.m[0][0] = newRight.x;	matrix.m[0][1] = newRight.y;	matrix.m[0][2] = newRight.z;	matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = newUp.x;		matrix.m[1][1] = newUp.y;		matrix.m[1][2] = newUp.z;		matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = newForward.x;	matrix.m[2][1] = newForward.y;	matrix.m[2][2] = newForward.z;	matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = pos.x;			matrix.m[3][1] = pos.y;			matrix.m[3][2] = pos.z;			matrix.m[3][3] = 1.0f;
	return matrix;

}

mat4 Matrix_QuickInverse(mat4& m) {
	mat4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

vec3d IntersectPlane(vec3d& plane_p, vec3d& plane_n, vec3d& lineStart, vec3d& lineEnd)
{
	plane_n = Vector_Normalise(plane_n);
	float plane_d = -Vector_DotProduct(plane_n, plane_p);
	float ad = Vector_DotProduct(lineStart, plane_n);
	float bd = Vector_DotProduct(lineEnd, plane_n);
	float t = (-plane_d - ad) / (bd - ad);
	vec3d lineStartToEnd = Vector_Sub(lineEnd, lineStart);
	vec3d lineToIntersect = Vector_Mul(lineStartToEnd, t);
	return Vector_Add(lineStart, lineToIntersect);
}

int clipping(vec3d plane_p, vec3d plane_n, triangle& in_tri, triangle& out_tri1, triangle& out_tri2) {
	plane_n = Vector_Normalise(plane_n);

	auto dis = [&](vec3d& p) {
		vec3d n = Vector_Normalise(p);
		return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - Vector_DotProduct(plane_n, plane_p));
	};

	vec3d* inside_points[3]; int inside_count = 0;
	vec3d* outside_points[3]; int outside_count = 0;

	float d0 = dis(in_tri.p[0]);
	float d1 = dis(in_tri.p[1]);
	float d2 = dis(in_tri.p[2]);

	if (d0 >= 0) { inside_points[inside_count++] = &in_tri.p[0]; }
	else { outside_points[outside_count++] = &in_tri.p[0]; }
	if (d1 >= 0) { inside_points[inside_count++] = &in_tri.p[1]; }
	else { outside_points[outside_count++] = &in_tri.p[1]; }
	if (d2 >= 0) { inside_points[inside_count++] = &in_tri.p[2]; }
	else { outside_points[outside_count++] = &in_tri.p[2]; }

	if (inside_count == 0) {
		return -1;
	}
	else if (outside_count == 0) {
		return 0;
	}
	else if (inside_count == 1 && outside_count == 2) {
		out_tri1.color[0] = in_tri.color[0];
		out_tri1.color[1] = in_tri.color[1];
		out_tri1.color[2] = in_tri.color[2];

		out_tri1.p[0] = *inside_points[0];

		out_tri1.p[1] = IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);
		out_tri1.p[2] = IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1]);

		return 1;
	}
	else if (inside_count == 2 && outside_count == 1) {
		out_tri1.color[0] = in_tri.color[0];
		out_tri1.color[1] = in_tri.color[1];
		out_tri1.color[2] = in_tri.color[2];

		out_tri2.color[0] = in_tri.color[0];
		out_tri2.color[1] = in_tri.color[1];
		out_tri2.color[2] = in_tri.color[2];


		out_tri1.p[0] = *inside_points[0];
		out_tri1.p[1] = *inside_points[1];
		out_tri1.p[2] = IntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0]);

		out_tri2.p[0] = *inside_points[1];
		out_tri2.p[1] = out_tri1.p[2];
		out_tri2.p[2] = IntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0]);

		return 2;
	}
}