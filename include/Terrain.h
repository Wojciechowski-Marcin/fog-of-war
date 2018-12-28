#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include "Position.h"
#include "Line.h"

class Terrain
{
  public:
    Terrain(const Position& windowSize);
    static std::vector<Line> getCollisionLines();
    static std::vector<Position> getCollisionPoints();
    void drawTerrain();
  private:
    static std::vector<Line> collisions;
};

#endif