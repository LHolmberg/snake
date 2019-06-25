#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <math.h>
#include <fstream>
#include <Windows.h>

unsigned int score;

bool moveForward = false;
bool moveBack = false;
bool moveLeft = false;
bool moveRight = false;

float Xposition, Yposition, Zposition;
float Xrotation, Yrotation, Zrotation;

float XRotationRadius, YRotationRadius;

GLdouble pillarXpos = 0;
GLdouble pillarZpos = -24;

class Player {
public:
	Player();
	~Player();

	void startup();
	void shutdown();

	void Forward(void);
	void Reverse(void);
	void Left(void);
	void Right(void);

	float vel = 0.15f;
};

Player::Player() { /* nothing here */}
Player::~Player() { /* nothing here */ }

void Player::startup()
{
	// set player pos
	Xrotation = 0;
	Yrotation = 765;
	Xposition = -23;
	Yposition = 2;
	Zposition = 30;
}

void Player::shutdown() {
	//TO-DO: free up memory
}

void Player::Forward(void)
{
	YRotationRadius = (Yrotation / 180 * 3.14);
	XRotationRadius = (Xrotation / 180 * 3.14);
	Xposition += float(sin(YRotationRadius)) * vel;
	Zposition -= float(cos(YRotationRadius)) * vel;
}

void Player::Reverse(void)
{
	YRotationRadius = (Yrotation / 180 * 3.14);
	XRotationRadius = (Xrotation / 180 * 3.14);
	Xposition -= float(sin(YRotationRadius)) * vel;
	Zposition += float(cos(YRotationRadius)) * vel;
}

void Player::Right(void)
{
	YRotationRadius = (Yrotation / 180 * 3.14);
	Xposition += float(cos(YRotationRadius)) * vel;
	Zposition += float(sin(YRotationRadius)) * vel;
}

void Player::Left(void) 
{
	YRotationRadius = (Yrotation / 180 * 3.14);
	Xposition -= float(cos(YRotationRadius)) * vel;
	Zposition -= float(sin(YRotationRadius)) * vel;
}
Player player;

class Camera {
public:
	Camera();
	~Camera();

	void shutdown();

	void input();
	void cam();
	float sens = 0.1f;
};

Camera::Camera(){  /*nothing here*/ }
Camera::~Camera(){ /*nothing here*/ }

void Camera::shutdown() { /*TO-DO: free up memory*/ }

void Camera::input() {
	int res = glfwJoystickPresent(GLFW_JOYSTICK_1);
	int btnCount;
	int count;
	
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &btnCount);
	const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

	if (glfwGetJoystickButtons)
		if (res == 1) {
			//movement (walking)
			if (axes[1] <= -0.45f)
				moveForward = true;
			else
				moveForward = false;

			if (axes[1] >= 0.45f)
				moveBack = true;
			else 
				moveBack = false;

			if (axes[0] <= -0.45f)
				moveLeft = true;
			else 
				moveLeft = false;

			if (axes[0] >= 0.45f)
				moveRight = true;
			else 
				moveRight = false;

			//camera movement (look around)
			if (axes[2] >= 0.45f) {
				Yrotation += 8 * sens;
			}

			if (axes[2] <= -0.45f) {
				Yrotation += -8 * sens;
			}
			
			if (axes[3] >= 0.45f) {
				Xrotation += 8 * sens;
			}
			
			if (axes[3] <= -0.45f) {
				Xrotation += -8 * sens;
			}
			glfwPollEvents();
		}

	if (moveForward)
		player.Forward();

	if (moveBack)
		player.Reverse();

	if (moveLeft)
		player.Left();

	if (moveRight)
		player.Right();
}

void Camera::cam() {
	glRotatef(Xrotation, 1.0, 0.0, 0.0);
	glRotatef(Yrotation, 0.0, 1.0, 0.0);
	glTranslated(-Xposition, -Yposition, -Zposition);

	if (Xrotation <= -89) {
		Xrotation = -89;
	}

	if (Xrotation >= 89) {
		Xrotation = 89;
	}
}
Camera camera;

typedef struct Objects {
	void DrawPillar(void) {
		glColor3f(1, 0.5, 0);
		glPushMatrix();
		glTranslated(pillarXpos, 3, pillarZpos);
		glScaled(1, 9, 1);
		glutSolidCube(3);
		glPopMatrix();
		glColor3f(0.04f, 0.7, 0.6);
	}
	void DrawGround(void) {
		glColor3f(0.1, 0.25, 0.25);
		glPushMatrix();
		glTranslated(25, Yposition - 4, -0);
		glScaled(150, 0.5f, 150);
		glutSolidCube(1);
		glPopMatrix();
	}
};
struct Objects ob;

//collision algorithm, AABB
double AABB(float dx, float dy, float dz) {
	return sqrt(dx * dx + dy * dy + dz * dz);
}

void finish() {
	if (score >= 7) {
		glutDestroyWindow(glutGetWindow());
		//system("start C:\\Users\\Lukas\\Desktop\\Alarmclock\\UI.py");
	}
}

void CheckCollision() {
	float distance = AABB(Xposition - pillarXpos, Yposition - 3, Zposition - pillarZpos);
	if (distance <= (2.5 + 2.5)) {
		pillarXpos = rand() % 60;
		pillarZpos = rand() % 60;
		score += 1;
		std::cout << score << std::endl;
	}
}

void Render(void) {
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.20, 0.20, 0.20, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//enables
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);

	//setup functions
	camera.cam();
	finish();
	CheckCollision();
	camera.input();

	//render blocks
	ob.DrawPillar();
	ob.DrawGround();
	
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
	//setup glut & glfw
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OPENGLGAME");
	glfwInit();

	//gameloop
	while (true) {
		glutDisplayFunc(Render);
		glutIdleFunc(Render);
		glutReshapeFunc(Window);
		glutMainLoop();
	}
	return 0;
}
