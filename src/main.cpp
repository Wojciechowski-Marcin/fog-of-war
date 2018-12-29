#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include "Sight.h"
#include "Terrain.h"
#include "Player.h"
#include "Position.h"
#include "Line.h"
#include "Controls.h"
#include "BulletControl.h"

Position windowSize = {1366, 768};

Sight sight;
Terrain terrain(windowSize);
Player player;
Controls controls;
BulletControl bulletControl;

Position mousePos = {0, 0};
std::vector<Position> points;

void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	sight.computeLight(player.position);
	player.drawPlayer();
	terrain.drawTerrain();
	controls.drawAim();
	bulletControl.drawBullets();

	glFlush();
}
void idleFunc()
{
	Player::move();
	BulletControl::moveBullets();
	glutPostRedisplay();
}

int main(int argcp, char **argv)
{
	glutInit(&argcp, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);
	windowSize.x = glutGet(GLUT_SCREEN_WIDTH);
	windowSize.y = glutGet(GLUT_SCREEN_HEIGHT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutCreateWindow("Fog of War");
	glutFullScreen();
	//glutReshapeWindow(windowSize.x, windowSize.y);
	glViewport(0, 0, windowSize.x, windowSize.y);
	glOrtho(0, windowSize.x, windowSize.y, 0, -1, 1);
	//glutSetCursor(GLUT_CURSOR_NONE);

	glutIdleFunc(idleFunc);
	glutDisplayFunc(displayFunc);
	//glutReshapeFunc(reshapeFunc);
	glutKeyboardFunc(controls.keyboardFunction);
	glutKeyboardUpFunc(controls.keyboardUpFunction);
	glutMouseFunc(controls.mouseClick);
	glutPassiveMotionFunc(controls.mouseMove);

	glutMainLoop();
	return 0;
}
