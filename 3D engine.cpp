#include "3D engine.h"

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "test");

const sf::Vector2i windowCenter(WIDTH / 2, HEIGHT / 2);
Cam cam({ 0.0f, -40.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 90, 5.0f);
Terrain terrain;
sf::VertexArray TriangleToDraw(sf::Triangles);
sf::VertexArray LineToDraw(sf::Lines);

float sign(vec3d p1, vec3d p2, vec3d p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(vec3d pt, vec3d v1, vec3d v2, vec3d v3)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

void draw_triangle(vec3d p1, vec3d p2, vec3d p3, int color[]) {
	sf::VertexArray tri(sf::Triangles, 3);

	tri[0].position = sf::Vector2f(p1.x, p1.y);
	tri[1].position = sf::Vector2f(p2.x, p2.y);
	tri[2].position = sf::Vector2f(p3.x, p3.y);
	tri[0].color = sf::Color((int)color[0], (int)color[1], (int)color[2]);
	tri[1].color = sf::Color((int)color[0], (int)color[1], (int)color[2]);
	tri[2].color = sf::Color((int)color[0], (int)color[1], (int)color[2]);

	TriangleToDraw.append(tri[0]);
	TriangleToDraw.append(tri[1]);
	TriangleToDraw.append(tri[2]);
}

void draw_line(vec3d p1, vec3d p2) {
	sf::Vector2f vp1 = sf::Vector2f(p1.x, p1.y);
	sf::Vector2f vp2 = sf::Vector2f(p2.x, p2.y);
	sf::Vertex line[] = {
		sf::Vertex(vp1),
		sf::Vertex(vp2)
	};
	LineToDraw.append(line[0]);
	LineToDraw.append(line[1]);
}

int main() {
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point end;
	std::chrono::high_resolution_clock::time_point last = std::chrono::high_resolution_clock::now();
	window.setMouseCursorVisible(false);
	bool cursor_move = false;
	sf::Mouse::setPosition(windowCenter, window);
	mesh cube;
	cube.getobj("Deer.obj");
	terrain.make_value();
	terrain.triangle_Strip();
	while (window.isOpen()) {
		bool p = false;
		TriangleToDraw.clear();
		LineToDraw.clear();
		start = std::chrono::high_resolution_clock::now();
		sf::Event event;
		sf::Vector2i pos;
		float x = sin(cam.rot.y) * cam.speed; float z = cos(cam.rot.y) * cam.speed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { x *= 2; z *= 2; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { cam.pos.x -= x; cam.pos.z -= z; /*terrain.p.x -= x; terrain.p.z -= z;*/ }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { cam.pos.x += x; cam.pos.z += z; /*terrain.p.x += x; terrain.p.z += z;*/ }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { cam.pos.x += z; cam.pos.z -= x; /*terrain.p.x += z; terrain.p.z -= x;*/ }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { cam.pos.x -= z; cam.pos.z += x; /*terrain.p.x -= z; terrain.p.z += x;*/ }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && cam.jumped == false) { cam.y_movement += cam.speed; cam.jumped = true; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) cam.fov += cam.fov + 0.01f >= 180 ? 0 : 0.01;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) cam.fov -= cam.fov - 0.01f <= 0 ? 0 : 0.01;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { cam.fov = 90.0f; cam.speed = 0.1f; }
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) p = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) cursor_move = true;
		else if (cursor_move) { cursor_move = false; sf::Mouse::setPosition(windowCenter, window); }
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (!cursor_move && (event.type == sf::Event::MouseLeft || event.type == sf::Event::MouseMoved) && sf::Mouse::getPosition(window) != windowCenter) {
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				int x_a = pos.x;
				int y_a = pos.y;
				float movex = (float)(x_a - windowCenter.x) / 500.0f;
				float movey = (float)(y_a - windowCenter.y) / 500.0f;
				cam.rot.x -= movey;
				cam.rot.y += movex;
				sf::Mouse::setPosition(windowCenter, window);
			}
		}
		sf::Vector2i now_pos = sf::Mouse::getPosition(window);
		if (cursor_move) {
			if (now_pos.x > WIDTH) { pos.x = WIDTH; sf::Mouse::setPosition(sf::Vector2i{ WIDTH, now_pos.y }, window); }
			else if (now_pos.x <= 0) { pos.x = 1; sf::Mouse::setPosition(sf::Vector2i{ 1, now_pos.y }, window); }
			else pos.x = now_pos.x;
			if (now_pos.y > HEIGHT) { pos.y = HEIGHT; sf::Mouse::setPosition(sf::Vector2i{ now_pos.x, HEIGHT }, window); }
			else if (now_pos.y <= 0) { pos.y = 1; sf::Mouse::setPosition(sf::Vector2i{ now_pos.x, 1 }, window); }
			else pos.y = now_pos.y;
		}
		else pos = windowCenter;
		cam.y_movement -= 0.75f;
		if (abs(terrain.p.x + width / 2 - cam.pos.x) >= scl || abs(terrain.p.z + width / 2 - cam.pos.z) >= scl) {
			terrain.p.x = (int)(cam.pos.x / scl) * scl - width / 2;
			terrain.p.z = (int)(cam.pos.z / scl) * scl - width / 2;
			terrain.make_value();
			terrain.triangle_Strip();
		}
		float lowest = noise(abs(cam.pos.z / scl) * Gscl, abs(cam.pos.x / scl) * Gscl) * 30 * height + 30;
		cam.pos.y += cam.y_movement;
		if (cam.pos.y <= lowest) { cam.pos.y = lowest; cam.y_movement = 0.0f; cam.jumped = false; }
		//cam.pos.y = terrain.h[wds / 2][wds / 2] * height + 30;

		window.clear(sf::Color(0, 0, 0));
		std::vector<triangle> triangles;
		for (int i = 0, len = terrain.tris.size(); i < len; i++) {
			terrain.tris[i].TriangleIndex = i;
			for (int r = 0; r < 3; r++) terrain.tris[i].TwoDp[r] = cam.get3dcoord(terrain.tris[i].p[r]);
			vec3d line1, line2, normal;
			line1.x = terrain.tris[i].TwoDp[1].x - terrain.tris[i].TwoDp[0].x;
			line1.y = terrain.tris[i].TwoDp[1].y - terrain.tris[i].TwoDp[0].y;
			line1.z = terrain.tris[i].TwoDp[1].z - terrain.tris[i].TwoDp[0].z;

			line2.x = terrain.tris[i].TwoDp[2].x - terrain.tris[i].TwoDp[0].x;
			line2.y = terrain.tris[i].TwoDp[2].y - terrain.tris[i].TwoDp[0].y;
			line2.z = terrain.tris[i].TwoDp[2].z - terrain.tris[i].TwoDp[0].z;
			normal.x = line1.y * line2.z - line1.z * line2.y;
			normal.y = line1.z * line2.x - line1.x * line2.z;
			normal.z = line1.x * line2.y - line1.y * line2.x;

			float l = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
			normal.x /= l; normal.y /= l; normal.z /= l;
			vec3d vCameraRay1 = Vector_Sub(terrain.tris[i].TwoDp[0], cam.pos);
			//printf("%f\n", normal.z);
			float n = Vector_DotProduct(normal, vCameraRay1);

			//printf("%f\n", n);
			if (true) {
				/*cube.tris[i]*/terrain.tris[i].normal = normal;
				terrain.tris[i].CamRay = vCameraRay1;
				terrain.tris[i].VDot = n;
				vec3d light = { 0.0f, 0.0f, 1.0f };
				float lNormal = sqrtf(powf(light.x, 2) + powf(light.y, 2) + powf(light.z, 2));
				light.x /= lNormal; light.y /= lNormal; light.z /= lNormal;

				float dp = std::max(0.3f, Vector_DotProduct(light, normal));
				float h = (terrain.tris[i].p[0].y + terrain.tris[i].p[1].y + terrain.tris[i].p[2].y) / 3;
				if (h >= height * scl * 0.8 * 0.3) {
					terrain.tris[i].color[0] = 255 * dp;
					terrain.tris[i].color[1] = 255 * dp;
					terrain.tris[i].color[2] = 255 * dp;
				}
				else if (h >= height * scl * 0.6 * 0.3) {
					terrain.tris[i].color[0] = 112 * dp;
					terrain.tris[i].color[1] = 84 * dp;
					terrain.tris[i].color[2] = 27 * dp;
				}
				else if (h >= height * scl * 0.3 * 0.3) {
					terrain.tris[i].color[0] = 17 * dp;
					terrain.tris[i].color[1] = 92 * dp;
					terrain.tris[i].color[2] = 64 * dp;
				}
				else {
					terrain.tris[i].color[0] = 24 * dp;
					terrain.tris[i].color[1] = 163 * dp;
					terrain.tris[i].color[2] = 156 * dp;
				}


				std::list<triangle> ZClippedTris = terrain.tris[i].GetZClippedTriangles();
				for (triangle t : ZClippedTris) {
					triangles.push_back(t);
				}
			}
		}
		std::sort(triangles.begin(), triangles.end(), [](triangle& t1, triangle& t2)
			{
				//float z1 = 0;
				//float z2 = 0;
				//for (int i = 0; i < 3; i++) {
				//	z1 += sqrtf(powf(t1.p[i].x, 2) + powf(t1.p[i].y, 2) + powf(t1.p[i].z, 2));
				//	z2 += sqrtf(powf(t2.p[i].x, 2) + powf(t2.p[i].y, 2) + powf(t2.p[i].z, 2));
				//}
				float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
				float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
				return z1 < z2;
			});
		triangle CameraOn;
		bool find = false;
		int i = 0;
		int TriIndex = 0;
		for (triangle tri : triangles) {
			vec3d projected[3];
			for (int i = 0; i < 3; i++) tri.TwoDp[i] = cam.get2dcoord(tri.p[i]);
			std::list<triangle> ClippedTris = tri.GetClippedTriangles();
			for (triangle t : ClippedTris) {
				//draw_line(t.p[0], t.p[1]);
				//draw_line(t.p[1], t.p[2]);
				//draw_line(t.p[2], t.p[0]);
				if (PointInTriangle(vec3d{ (float)pos.x, (float)pos.y, 0 }, t.p[0], t.p[1], t.p[2])) {
					if (!find || (t.p[0].z + t.p[1].z + t.p[2].z) / 3 > (CameraOn.p[0].z + CameraOn.p[1].z + CameraOn.p[2].z) / 3) {
						CameraOn = t;
						TriIndex = i;
					}
					find = true;
				}
				draw_triangle(t.p[0], t.p[1], t.p[2], t.color);
			}
			i++;
		}
		if (find){
			//int c[3] = { 255, 0, 0 };
			//draw_triangle(CameraOn.p[0], CameraOn.p[1], CameraOn.p[2], c);
			draw_line(CameraOn.p[0], CameraOn.p[1]);
			draw_line(CameraOn.p[1], CameraOn.p[2]);
			draw_line(CameraOn.p[2], CameraOn.p[0]);
			//if (p && find) printf("Normal: %f\nvCameraRay: %f, %f, %f\nVector DotProduct: %f\nTriangle Point1: %f, %f, %f\nTriangle Point2: %f, %f, %f\nTrianlge Point3: %f, %f, %f\nCamera pos: %f, %f, %f\n\n",
			//	CameraOn.normal.z,
			//	CameraOn.VDot,
			//	CameraOn.CamRay.x, CameraOn.CamRay.y, CameraOn.CamRay.z,
			//	triangles[TriIndex].p[0].x, triangles[TriIndex].p[0].y, triangles[TriIndex].p[0].z,
			//	triangles[TriIndex].p[1].x, triangles[TriIndex].p[1].y, triangles[TriIndex].p[1].z,
			//	triangles[TriIndex].p[2].x, triangles[TriIndex].p[2].y, triangles[TriIndex].p[2].z,
			//	cam.pos.x, cam.pos.y, cam.pos.z);
			//if (p) {
			//	for (int i = 0; i < 3; i++) {
			//		//int a = abs(CameraOn.p[i].z / scl) * Gscl, b = abs(CameraOn.p[i].x / scl) * Gscl;
			//		//auto iter = terrain.Extraheight.find(std::make_pair(a, b));
			//		//if (iter != terrain.Extraheight.end()) {
			//		//	iter->second += 10.0f;
			//		//}
			//		//else {
			//		//	terrain.Extraheight[std::make_pair(a, b)] = 10.0f;
			//		//}
			//		terrain.tris[CameraOn.TriangleIndex].p[i].y += 1.0f;
			//	}
			//}
		}
		draw_line(vec3d{ (float)pos.x - 10, (float)pos.y }, vec3d{ (float)pos.x + 10, (float)pos.y });
		draw_line(vec3d{ (float)pos.x, (float)pos.y - 10 }, vec3d{ (float)pos.x, (float)pos.y + 10 });
		window.draw(TriangleToDraw);
		window.draw(LineToDraw);
		window.display();
	}
	return 0;
}
