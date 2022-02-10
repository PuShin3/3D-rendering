#include "Terrain.h"

void Terrain::make_value() {
	for (int y = 0; y < wds; y++) {
		for (int x = 0; x < wds; x++) {
			int a = abs(p.z / scl + x) * Gscl, b = abs(p.x / scl + y) * Gscl;
			auto iter = queue.find(std::make_pair(a, b));
			if (iter == queue.end()) {
				float n = noise(a, b) * 30;
				queue[std::make_pair(a, b)] = n;
				h[y][x] = n;
			}
			else {
				h[y][x] = iter->second;
			}
			
		}
	}
}

void Terrain::triangle_Strip() {
	tris.clear();
	for (int i = 0; i < 2; i++) {
		for (int y = 0; y < wds; y++) {
			for (int x = 0; x < wds; x++) {
				if (x + 1 < wds && y + 1 < wds) {
					vec3d point[3];
					triangle out;
					std::vector<triangle> t;
					int a = abs(p.z / scl + x) * Gscl, b = abs(p.x / scl + y) * Gscl;
					auto iter = Extraheight.find(std::make_pair(a, b));
					int extraH = 0;
					if (iter != Extraheight.end()) {
						extraH = iter->second;
					}
					switch (i) {
					case 0:
						point[0] = { (float)(y + 1) * scl + p.x, height * h[y + 1][x + 1], (float)(x + 1) * scl + p.z };
						point[1] = { (float)y * scl + p.x, height * h[y][x], (float)x * scl + p.z };
						point[2] = { (float)y * scl + p.x, height * h[y][x + 1], (float)(x + 1) * scl + p.z };
						out = { point[0], point[1], point[2] };
						//t = out.RTIN(scl, height, i);
						break;
					case 1:
						point[0] = { (float)(y + 1) * scl + p.x, height * h[y + 1][x + 1], (float)(x + 1) * scl + p.z };
						point[2] = { (float)y * scl + p.x, height * h[y][x], (float)x * scl + p.z };
						point[1] = { (float)(y + 1) * scl + p.x, height * h[y + 1][x], (float)x * scl + p.z };
						out = { point[0], point[1], point[2] };
						break;
					};
					tris.push_back(out);
				}
			}
		}
	}
}