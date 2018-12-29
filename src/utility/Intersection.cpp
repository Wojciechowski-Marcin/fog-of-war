#include <vector>
#include <cmath>
#include <algorithm>
#include "Intersection.h"
#include "Position.h"
#include "Line.h"

Position Intersection::checkIntersection(const Position &source, const Position& target, const std::vector<Line> &collisions)
{
    Intersect closestIntersect{{-1, -1}, __INT_MAX__};
    for (const auto &collision : collisions)
    {
        Intersect intersection;
        intersection = findIntersection(source, target, collision);
        if (intersection.T1 == __INT_MAX__)
            continue;
        if (closestIntersect.T1 == __INT_MAX__ || intersection.T1 < closestIntersect.T1)
            closestIntersect = intersection;
    }
    return closestIntersect.pos;
}

Intersection::Intersect Intersection::findIntersection(const Position &source, const Position &target, const Line &terrain)
{
    // return value
    Intersect ret = {target, __INT_MAX__};

    // ray in parametric (point + direction * T1)
    double r_px = source.x;
    double r_py = source.y;
    double r_dx = target.x - source.x;
    double r_dy = target.y - source.y;

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