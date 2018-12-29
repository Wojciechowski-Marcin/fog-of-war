#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include "Position.h"
#include "Line.h"

class Intersection
{
  private:
  public:
    struct Intersect
    {
        Position pos;
        double T1;
    };
    Position checkIntersection(const Position &source, const Position &target, const std::vector<Line> &collisions);
    Intersect findIntersection(const Position &source, const Position &target, const Line &terrain);
};

#endif