#include <GL/freeglut.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "objects.h"
#include "camera.h"
#include "collision.h"


objects obje;
camera cam;
collision col;

void Render(void) {
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.20, 0.20, 0.20, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	std::cout << glfwJoystickPresent(GLFW_JOYSTICK_1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	obje.RenderObjects();
	cam.input();

	col.CollisionCheck();
	
	//exit if all is collected
	if (!obje.cube1 && !obje.cube2 && !obje.cube3 &&
		!obje.cube4 && !obje.cube5 && !obje.cube6)
	{
		glutDestroyWindow(glutGetWindow());
	}
	glutSwapBuffers();
}

void Window(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1500, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OPENGLGAME");
	glfwInit();
	cam.startup();
	
	while (true) {
		glutDisplayFunc(Render);
		glutIdleFunc(Render);
		glutReshapeFunc(Window);
		glutMainLoop();
	}
	return 0;
}