#ifndef BULLETCONTROL_H
#define BULLETCONTROL_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include "Position.h"
#include "Bullet.h"

class BulletControl {
    public:
        void drawBullets();
        static void moveBullets();
        static void addBullet(Bullet& bullet);
    private: 
        static std::vector<Bullet> bullets;
};

#endif