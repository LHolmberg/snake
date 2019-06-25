#include "collision.h"

objects obj;


double collision::AABB(float dx, float dy, float dz) {
	return sqrt(dx * dx + dy * dy + dz * dz);
}

void collision::CollisionCheck() {
	float distance2 = AABB(cam.Xpos - 10, cam.Ypos - 0, cam.Zpos - 4);

	if (distance2 <= (2.5 + 2.5)) {
		obj.cube2 = false;
	}

	float distance = AABB(cam.Xpos - 12, cam.Ypos - 3, cam.Zpos - (-25));
	if (distance <= (2.5 + 2.5)) {
		obj.cube1 = false;
	}
	float distance3 = AABB(cam.Xpos - 23, cam.Ypos - 0, cam.Zpos - 8);
	if (distance3 <= (2.5 + 2.5)) {
		obj.cube3 = false;
	}

	float distance4 = AABB(cam.Xpos - 45, cam.Ypos - 0, cam.Zpos - 25);
	if (distance4 <= (2.5 + 3.5)) {
		obj.cube4 = false;
	}

	float distance5 = AABB(cam.Xpos - 73, cam.Ypos - 0, cam.Zpos - (-35));
	if (distance5 <= (2.5 + 2.5)) {
		obj.cube5 = false;
	}

	float distance6 = AABB(cam.Xpos - 90, cam.Ypos - 0, cam.Zpos - (-55));
	if (distance6 <= (4 + 4)) {
		obj.cube6 = false;
	}
}
