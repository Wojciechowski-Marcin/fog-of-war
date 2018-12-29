#ifndef SIGHT_H
#define SIGHT_H

#include <vector>
#include "Position.h"
#include "Line.h"

class Sight
{
  public:
    void computeLight(const Position &player);

  private:
    std::vector<Position> rays;
    static Position playerPos;

    void getRays(const std::vector<Position> &collisionPoints);
    void sortRays();
    static bool angleSort(const Position &p1, const Position &p2);
    void drawRays();
};

#endif