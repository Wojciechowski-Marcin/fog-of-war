#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm>
#include <vector>
#include "Terrain.h"
#include "Line.h"

std::vector<Line> Terrain::collisions;

Terrain::Terrain(const Position& windowSize)
{
    collisions.push_back({{windowSize.x / 4, 3 * windowSize.y / 4}, {windowSize.x / 4, windowSize.y / 4}});
    collisions.push_back({{windowSize.x / 4, 3 * windowSize.y / 4}, {windowSize.x / 4 + 50, 3 * windowSize.y / 4}});
    collisions.push_back({{windowSize.x / 4, windowSize.y / 4}, {windowSize.x / 4 + 50, windowSize.y / 4}});
    collisions.push_back({{windowSize.x / 4 + 50, 3 * windowSize.y / 4}, {windowSize.x / 4 + 50, windowSize.y / 4}});
    collisions.push_back({{3 * windowSize.x / 4, 3 * windowSize.y / 4}, {3 * windowSize.x / 4, windowSize.y / 4}});
        // border
    collisions.push_back({{0, 0}, {windowSize.x, 0}});
    collisions.push_back({{0, windowSize.y}, {0, 0}});
    collisions.push_back({{windowSize.x, 0}, {windowSize.x, windowSize.y}});
    collisions.push_back({{windowSize.x, windowSize.y}, {0, windowSize.y}});
}

std::vector<Line> Terrain::getCollisionLines(){
    return collisions;
}

std::vector<Position> Terrain::getCollisionPoints(){
    std::vector<Position> points;
	for (Line line : collisions) {
		if (std::find(points.begin(), points.end(), line.a) == points.end())
			points.push_back(line.a);
		if (std::find(points.begin(), points.end(), line.b) == points.end())
			points.push_back(line.b);
	}
    return points;
}

void Terrain::drawTerrain(){
    glBegin(GL_LINES);
    glColor3f(0.5f, .5f, .5f);
    for (Line line : collisions)
    {
        glVertex2f(line.a.x, line.a.y);
        glVertex2f(line.b.x, line.b.y);
    }
    glEnd();
}