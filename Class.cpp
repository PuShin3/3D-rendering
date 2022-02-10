	#include "Class.h"

	Cam::Cam(vec3d p, vec3d r, float f, float s) {
		pos = p;
		rot = r;
		fov = f;
		speed = s;
	}

	vec3d Cam::get3dcoord(vec3d p) {
		float mx = p.x - pos.x;
		float my = p.y - pos.y;
		float mz = p.z - pos.z;
		float dx = cos(rot.y) * (sin(rot.z) * my + cos(rot.z) * mx) - sin(rot.y) * mz;
		float dy = sin(rot.x) * (cos(rot.y) * mz + sin(rot.y) * (sin(rot.z) * my + cos(rot.z) * mx)) + cos(rot.x) * (cos(rot.z) * my + sin(rot.z) * mx);
		float dz = cos(rot.x) * (cos(rot.y) * mz + sin(rot.y) * (sin(rot.z) * my + cos(rot.z) * mx)) - sin(rot.x) * (cos(rot.z) * my + sin(rot.z) * mx);
		return { dx, dy, dz };
	}

	vec3d Cam::get2dcoord(vec3d p) {
		float e = (float)tan(fov / 2) * (float)(WIDTH / 2);
		float x = (WIDTH / 2) + (e * p.x) / p.z;
		float y = (HEIGHT / 2) + (e * p.y) / p.z;
		return { x, y, p.z };
	}

float Cam::distance(vec3d p1) {
	return sqrt(pow(p1.x - pos.x, 2) + pow(p1.y - pos.y, 2) + pow(p1.z - pos.z, 2));
}

//float Terrain::Noise(int i, int x, int y) {
//	int n = x + y * 57;
//	n = (n << 13) ^ n;
//	int a = primes[i][0], b = primes[i][1], c = primes[i][2];
//	int t = (n * (n * n * a + b) + c) & 0x7fffffff;
//	return 1.0 - (float)(t) / 1073741824.0;
//}
//
//float Terrain::SmoothedNoise(int i, int x, int y) {
//	float corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) +
//		Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 16,
//		sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) +
//			Noise(i, x, y + 1)) / 8,
//		center = Noise(i, x, y) / 4;
//	return corners + sides + center;
//}
//
//float Terrain::Interpolate(float a, float b, float x) {
//	float ft = x * 3.1415927,
//		f = (1 - cos(ft)) * 0.5;
//	return  a * (1 - f) + b * f;
//}
//
//float Terrain::InterpolatedNoise(int i, float x, float y) {
//	int integer_X = x;
//	float fractional_X = x - integer_X;
//	int integer_Y = y;
//	float fractional_Y = y - integer_Y;
//
//	float v1 = SmoothedNoise(i, integer_X, integer_Y),
//		v2 = SmoothedNoise(i, integer_X + 1, integer_Y),
//		v3 = SmoothedNoise(i, integer_X, integer_Y + 1),
//		v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1),
//		i1 = Interpolate(v1, v2, fractional_X),
//		i2 = Interpolate(v3, v4, fractional_X);
//	return Interpolate(i1, i2, fractional_Y);
//}
//
//float Terrain::ValueNoise_2D(float x, float y) {
//	float total = 0,
//		frequency = pow(2, numOctaves),
//		amplitude = 1;
//	for (int i = 0; i < numOctaves; ++i) {
//		frequency /= 2;
//		amplitude *= persistence;
//		total += InterpolatedNoise((primeIndex + i) % 10,
//			x / frequency, y / frequency) * amplitude;
//	}
//	return total / frequency;
//}
//
//void Terrain::make_value() {
//	for (int y = 0; y < wds; y++) {
//		for (int x = 0; x < wds; x++) {
//			t[y][x] = ValueNoise_2D(x, y) * height;
//		}
//	}
//}
//
//void Terrain::triangle_strip(float points[wds][wds]) {
//	for (int i = 0; i < 2; i++) {
//		for (int y = 0; y < wds; y++) {
//			for (int x = 0; x < wds; x++) {
//				if (x + 1 < wds && y + 1 < wds) {
//					vec3d p[3];
//					switch (i) {
//					case 0:
//						p[0] = { -width / 2 + (float)(y + 1) * scl, -height * scl / 2 + height * points[y + 1][x + 1], -width / 2 + (float)(x + 1) * scl };
//						p[1] = { -width / 2 + (float)y * scl, -height * scl / 2 + height * points[y][x], width / 2 + (float)x * scl };
//						p[2] = { -width / 2 + (float)y * scl, -height * scl / 2 + height * points[y][x + 1], -width / 2 + (float)(x + 1) * scl };
//						break;
//					case 1:
//						p[0] = { -width / 2 + (float)(y + 1) * scl, -height * scl / 2 + height * points[y + 1][x + 1], -width / 2 + (float)(x + 1) * scl };
//						p[1] = { -width / 2 + (float)(y + 1) * scl, -height * scl / 2 + height * points[y + 1][x], -width / 2 + (float)x * scl };
//						p[2] = { -width / 2 + (float)y * scl, -height * scl / 2 + height * points[y][x], -width / 2 + (float)x * scl };
//						break;
//					};
//					triangle out = { p[0], p[1], p[2] };
//					tris.push_back(out);
//				}
//			}
//		}
//	}
//}
//
//void Terrain::move_vertical(int n) {
//	if (n > 0) {
//		for (int y = wds - n - 1; y >= 0; y--) {
//			for (int x = 0; x < wds; x++) {
//				t[y + n][x] = t[y][x];
//			}
//		}
//		for (int y = 0; y < n; y++) {
//			for (int x = 0; x < wds; x++) {
//				t[y][x] = ValueNoise_2D(y, x);
//			}
//		}
//	}
//	else {
//		for (int y = -n; y < wds; y++) {
//			for (int x = 0; x < wds; x++) {
//				t[y + n][x] = t[y][x];
//			}
//		}
//		for (int y = wds - 1; y > wds + n; y--) {
//			for (int x = 0; x < wds; x++) {
//				t[y][x] = ValueNoise_2D(y, x);
//			}
//		}
//	}
//}
//
//void Terrain::move_horizontal(int n) {
//	if (n > 0) {
//		for (int y = 0; y < wds; y++) {
//			for (int x = wds - n - 1; x >= n; x--) {
//				t[y][x + n] = t[y][x];
//			}
//		}
//		for (int y = 0; y < n; y++) {
//			for (int x = 0; x < n; x++) {
//				t[y][x] = ValueNoise_2D(y, x);
//			}
//		}
//	}
//	else {
//		for (int y = 0; y < wds; y++) {
//			for (int x = -n; x < wds; x++) {
//				t[y][x + n] = t[y][x];
//			}
//		}
//		for (int y = 0; y < wds; y++) {
//			for (int x = wds - 1; x < wds - n; x++) {
//				t[y][x] = ValueNoise_2D(y, x);
//			}
//		}
//	}
//}