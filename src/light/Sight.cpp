#include <cmath>
#include <algorithm>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Sight.h"
#include "Terrain.h"
#include "Position.h"
#include "Intersection.h"
#include "Line.h"

Position Sight::playerPos = {0, 0};

void Sight::computeLight(const Position& player)
{
    playerPos = player;
    rays.clear();
    getRays(Terrain::getCollisionPoints());
    Intersection is;
    for(unsigned i=0; i <rays.size(); i++){
        Position pos = is.checkIntersection(playerPos, rays[i], Terrain::getCollisionLines());
        if(pos.x != -1 && pos.y != -1)
            rays[i] = pos;
    }
    sortRays();
    drawRays();
}

void Sight::getRays(const std::vector<Position> &collisionPoints)
{
    for (const auto& point : collisionPoints)
    {
        double angle = 0.1;
        rays.push_back(Position{point.x - angle, point.y - angle});
        rays.push_back(Position{point.x, point.y});
        rays.push_back(Position{point.x + angle, point.y + angle});
    }
}

void Sight::sortRays()
{
    std::sort(rays.begin(), rays.end(), angleSort);
}

bool Sight::angleSort(const Position& p1, const Position& p2)
{
    double a1 = atan2(p1.y - playerPos.y, p1.x - playerPos.x);
    double a2 = atan2(p2.y - playerPos.y, p2.x - playerPos.x);
    if (a1 < 0)
        a1 += 2 * M_PI;
    if (a2 < 0)
        a2 += 2 * M_PI;
    return a1 < a2;
}

void Sight::drawRays()
{
    glColor3f(0.5f, 0.f, .0f);
    glBegin(GL_TRIANGLES);
    for (unsigned i = 0; i < rays.size() - 1; i++)
    {
        glVertex2f(playerPos.x, playerPos.y);
        glVertex2f(rays[i].x, rays[i].y);
        glVertex2f(rays[i + 1].x, rays[i + 1].y);
    }
    glVertex2f(playerPos.x, playerPos.y);
    glVertex2f(rays[rays.size() - 1].x, rays[rays.size() - 1].y);
    glVertex2f(rays[0].x, rays[0].y);
    glEnd();
}
