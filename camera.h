#pragma once
#include <math.h>
#include <GLFW/glfw3.h>
#include <iostream>


class camera
{
public:

	void startup();

	void shutdown();

	void Forward();
	void Reverse();
	void Right();
	void Left();

	void input();

	double Xpos, Ypos, Zpos, Xrot, Yrot, Zrot, XRotRad, YRotRad;
};

