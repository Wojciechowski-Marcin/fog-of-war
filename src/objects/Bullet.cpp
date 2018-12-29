#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "Bullet.h"
#include "Terrain.h"
#include "BulletControl.h"

void Bullet::drawBullet() {
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    for(double i = 0; i < 2*M_PI; i+=0.1){
        double x1 = currentPosition.x + radius * cos(i);
        double y1 = currentPosition.y + radius * sin(i);
        glVertex2f(x1, y1);
    }
    glEnd();
}

void Bullet::moveBullet() {
    currentPosition.x += speed * cos(direction);
    currentPosition.y += speed * sin(direction);
    checkCollision();
}

void Bullet::checkCollision() {
    for (auto line : Terrain::getCollisionLines())
    {
        double xLine = line.a.x > line.b.x ? line.b.x : line.a.x;
        double yLine = line.a.y > line.b.y ? line.b.y : line.a.y;
        bool xCollision = currentPosition.x + radius >= xLine &&
                          xLine + abs(line.a.x - line.b.x) >= currentPosition.x;
        bool yCollision = currentPosition.y + radius >= yLine &&
                          yLine + abs(line.a.y - line.b.y) >= currentPosition.y;
        if (xCollision && yCollision)
            destroyed = 1;
    }
}