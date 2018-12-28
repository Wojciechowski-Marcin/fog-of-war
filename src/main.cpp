#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm>
#include <vector>
#include <cmath>
#include "Sight.h"
#include "Terrain.h"
#include "Player.h"
#include "Position.h"
#include "Line.h"
#include "Controls.h"

Position windowSize = {500.0f, 600.0f};
Sight sight;
Terrain terrain(windowSize);
Player player;
Controls controls;

Position mousePos = {0, 0};
std::vector<Position> points;

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	sight.computeLight(player.position);
	player.drawPlayer();
	terrain.drawTerrain();

	glFlush();
}
void idleFunc(){
	Player::move();
	glutPostRedisplay();
}

int main(int argcp, char **argv)
{
	glutInit(&argcp, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Fog of War");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutReshapeWindow(windowSize.x, windowSize.y);
	glOrtho(0, windowSize.x, windowSize.y, 0, 0, 1);
	glutIdleFunc(idleFunc);
	glutDisplayFunc(drawScene);
	glutPassiveMotionFunc(controls.mouseFunction);
	glutKeyboardFunc(controls.keyboardFunction);
	glutKeyboardUpFunc(controls.keyboardUpFunction);
	glutMainLoop();
	return 0;
}
