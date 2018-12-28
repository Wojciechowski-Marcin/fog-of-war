#ifndef PLAYER_H
#define PLAYER_H

#include "Position.h"

class Player
{
  public:
    static Position position;
    static void move();
    static bool checkCollision();
    void drawPlayer();
  private:
    static float speed;
    static int size;
};

#endif