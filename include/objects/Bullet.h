#ifndef BULLET_H
#define BULLET_H

#include <GL/glew.h>
#include <GL/glut.h>
#include "Position.h"

class Bullet
{
  public:
  /** ctor */
	Bullet(Position start, Position target_) : startingPosition(start), currentPosition(start), target(target_){};
  /** getters & setters */
	Position getStartingPosition() { return startingPosition; }
	Position getTarget() { return target; }
	void setTarget(Position target_) { target = target_; }
	double getDirection() { return direction; }
	void setDirection(double direction_) { direction = direction_; }
	bool isDestroyed() { return destroyed; }
	
	void drawBullet();
	void moveBullet();
	void checkCollision();

  private:
	Position startingPosition;
	Position target;
	Position currentPosition;
	double direction;
	double speed = 2.0f;
	int radius = 2;
	bool destroyed = 0;
};

#endif