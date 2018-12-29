#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "Player.h"
#include "Controls.h"
#include "Terrain.h"
#include "BulletControl.h"

float Player::speed = 1.0f;

int Player::size = 10;

Position Player::position = {200, 200};

void Player::shoot(Position mousePosition) {
    Bullet bullet = Bullet(position, mousePosition);
    BulletControl::addBullet(bullet);
}

void Player::move()
{
    for (auto Key : Controls::keysPressed)
    {
        Position prev = position;
        switch (Key)
        {
        case 'w':
            position.y -= speed;
            break;
        case 'a':
            position.x -= speed;
            break;
        case 's':
            position.y += speed;
            break;
        case 'd':
            position.x += speed;
            break;
        }
        if (checkCollision())
            position = prev;
    }
    glutPostRedisplay();
}

bool Player::checkCollision()
{
    for (auto line : Terrain::getCollisionLines())
    {
        double xLine = line.a.x > line.b.x ? line.b.x : line.a.x;
        double yLine = line.a.y > line.b.y ? line.b.y : line.a.y;
        bool xCollision = position.x + size >= xLine &&
                          xLine + abs(line.a.x - line.b.x) >= position.x - size;
        bool yCollision = position.y + size >= yLine &&
                          yLine + abs(line.a.y - line.b.y) >= position.y - size;
        if (xCollision && yCollision)
            return true;
    }
    return false;
}

void Player::drawPlayer()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(position.x - size, position.y - size);
    glVertex2f(position.x + size, position.y - size);
    glVertex2f(position.x + size, position.y + size);
    glVertex2f(position.x - size, position.y + size);
    glEnd();
}