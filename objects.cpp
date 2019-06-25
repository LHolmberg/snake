#include "objects.h"


void objects::RenderObjects() {

	if (cube1) {
		glColor3f(1, 0.5, 0);
		glPushMatrix();
		glTranslated(12, 3, -25);
		glScaled(1, 9, 1);
		glutSolidCube(3);
		glPopMatrix();
		glColor3f(0.04f, 0.7, 0.6);
	}
	glutSolidCube(0);
	

	if (cube2) {
		glColor3d(0.67, 0.21, 0.5);
		glPushMatrix();
		glTranslated(10, 0, 4);
		glutSolidCube(4);
		glPopMatrix();
	}
	glutSolidCube(0);

	if (cube3) {
		glColor3f(0.2, 0.5, 0);
		glPushMatrix();
		glTranslated(23, 0, 8);
		glScaled(1, 3, 1);
		glutSolidCube(3);
		glPopMatrix();
		glColor3f(0.04f, 0.7, 0.6);
	}
	glutSolidCube(0);

	if (cube4) {
		glColor3f(0.2, 0.333, 0);
		glPushMatrix();
		glTranslated(45, 0, 25);
		glScaled(2, 1, 2);
		glutSolidCube(3);
		glPopMatrix();
		glColor3f(0.04f, 0.7, 0.6);
	}
	glutSolidCube(0);

	if (cube5) {
		glColor3f(1, 0.333, 0.2);
		glPushMatrix();
		glTranslated(73, 0, -35);
		glScaled(2, 12, 2);
		glutSolidCube(3);
		glPopMatrix();
		glColor3f(0.04f, 0.7, 0.6);
	}
	glutSolidCube(0);

	if (cube6) {
		glColor3f(1, 1, 0.5);
		glPushMatrix();
		glTranslated(90, 0, -55);
		glScaled(3, 2, 3);
		glutSolidCube(3);
		glPopMatrix();
		glColor3f(0.04f, 0.7, 0.6);
	}
	glutSolidCube(0);
}
