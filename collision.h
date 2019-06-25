#pragma once
#include "objects.h"
#include <math.h>
#include "camera.h"

class collision
{
public:

	void CollisionCheck();
	
	void shutdown();

	double AABB(float dx, float dy, float dz);

	camera cam;
};

