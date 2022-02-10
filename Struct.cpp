#include "Struct.h"

void mesh::getobj(std::string filename) {
	srand(time(NULL));
	std::ifstream f(filename);

	while (!f.eof()) {
		std::string line;
		std::getline(f, line);

		if (line[0] == 'v') {
			std::strstream s;
			s << line;

			char junk;
			vec3d v;
			s >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}
		if (line[0] == 'f') {
			int f[3];
			std::vector<std::string> lines = split(line, " ");
			for (int i = 1; i < 4; i++) {
				std::vector<std::string> elements = split(lines[i], "/");
				f[i - 1] = std::stoi(elements[0]);
			}
			tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] , { rand() % 256, rand() % 256, rand() % 256} });
		}
	}
}

std::vector<std::string> mesh::split(const std::string& str, const std::string& pattern) {
	std::vector<std::string> result;
	std::string::size_type begin, end;

	end = str.find(pattern);
	begin = 0;

	while (end != std::string::npos) {
		if (end - begin != 0) {
			result.push_back(str.substr(begin, end - begin));
		}
		begin = end + pattern.size();
		end = str.find(pattern, begin);
	}

	if (begin != str.length()) {
		result.push_back(str.substr(begin));
	}
	return result;
}