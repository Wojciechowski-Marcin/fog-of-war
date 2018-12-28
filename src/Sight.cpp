#include <cmath>
#include <algorithm>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Sight.h"
#include "Terrain.h"
#include "Position.h"
#include "Line.h"

Position Sight::playerPos = {0, 0};

void Sight::computeLight(const Position& player)
{
    playerPos = player;
    rays.clear();
    getRays(Terrain::getCollisionPoints());
    setIntersections(Terrain::getCollisionLines());
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

// get closest intersection for each ray
void Sight::setIntersections(const std::vector<Line> &collisions)
{
    for (unsigned i = 0; i < rays.size(); i++)
    {
        Intersection closestIntersect{{0, 0}, __INT_MAX__};
        for (const auto& collision : collisions)
        {
            Intersection intersection;
            intersection = findIntersection(rays[i], collision);
            if (intersection.T1 == __INT_MAX__)
                continue;
            if (closestIntersect.T1 == __INT_MAX__ || intersection.T1 < closestIntersect.T1)
                closestIntersect = intersection;
        }
        rays[i] = closestIntersect.pos;
    }
}

Sight::Intersection Sight::findIntersection(const Position& ray, const Line& terrain)
{
    // return value
    Intersection ret = {ray, __INT_MAX__};

    // ray in parametric (point + direction * T1)
    double r_px = playerPos.x;
    double r_py = playerPos.y;
    double r_dx = ray.x - playerPos.x;
    double r_dy = ray.y - playerPos.y;

    // terrain in parametric
    double t_px = terrain.a.x;
    double t_py = terrain.a.y;
    double t_dx = terrain.b.x - terrain.a.x;
    double t_dy = terrain.b.y - terrain.a.y;

    // parallel lines?
    double r_mag = sqrt(r_dx * r_dx + r_dy * r_dy);
    double t_mag = sqrt(t_dx * t_dx + t_dy * t_dy);
    if (t_mag == 0 || r_mag == 0)
        return ret;
    if (r_dx / r_mag == t_dx / t_mag && r_dy / r_mag == t_dy / t_mag)
        return ret;

    // check collision
    double T2 = (r_dx * (t_py - r_py) + r_dy * (r_px - t_px)) / (t_dx * r_dy - t_dy * r_dx);
    double T1 = (t_px + t_dx * T2 - r_px) / r_dx;

    if (T1 < 0)
        return ret;
    if (T2 < 0 || T2 > 1)
        return ret;
    if (T1 != T1 || T2 != T2)
        return ret;

    ret.pos.x = r_px + r_dx * T1;
    ret.pos.y = r_py + r_dy * T1;
    ret.T1 = T1;
    return ret;
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
