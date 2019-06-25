#include "camera.h"

void camera::Forward() {
	YRotRad = (Yrot / 180 * 3.14);
	XRotRad = (Xrot / 180 * 3.14);
	Xpos += sin(YRotRad) * 5;
	Zpos -= cos(YRotRad) * 5;

}

void camera::Reverse() {
	YRotRad = (Yrot / 180 * 3.14);
	XRotRad = (Xrot / 180 * 3.14);
	Xpos -= sin(YRotRad) * 5;
	Zpos += cos(YRotRad) * 5;

}

void camera::Left() {
	YRotRad = (Yrot / 180 * 3.14);
	Xpos -= cos(YRotRad) * 5;
	Zpos -= sin(YRotRad) * 5;
}

void camera::Right() {
	YRotRad = (Yrot / 180 * 3.14);
	Xpos += cos(YRotRad) * 5;
	Zpos += sin(YRotRad) * 5;

}

void camera::input()
{
	int res = glfwJoystickPresent(GLFW_JOYSTICK_1);
	int btnCount;
	int count;
	
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &btnCount);
	const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

	if (glfwGetJoystickButtons)
		if (res == 1) {
			//joystick movement
			if (axes[1] <= -0.45f) {
				Forward();
			}
			if (axes[1] >= 0.45f) {
				Reverse();
			}
			if (axes[0] <= -0.45f) {
				Left();
			}
			if (axes[0] >= 0.45f) {
				Right();
			}

			//joystick mouse movement
			if (axes[2] >= 0.45f) {
				Yrot += 8 * 5;
			}

			if (axes[2] <= -0.45f) {
				Yrot += -8 * 5;
			}

			if (axes[3] >= 0.45f) {
				Xrot += 8 * 5;
			}

			if (axes[3] <= -0.45f) {
				Xrot += -8 * 5;
			}
			glfwPollEvents();
		}

	if (Xrot <= -89) {
		Xrot = -89;
	}

	if (Xrot >= 89) {
		Xrot = 89;
	}
}

void camera::startup() {
	glRotatef(Xrot, 1.0, 0.0, 0.0);
	glRotatef(Yrot, 0.0, 1.0, 0.0);
	glTranslated(-Xpos, -Ypos, -Zpos);
	
	//starting pos
	Xrot = 0;
	Yrot = 765;
	Xpos = -23;
	Ypos = 2;
	Zpos = 30;
}

