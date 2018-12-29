#include "BulletControl.h"
#include "Intersection.h"
#include "Terrain.h"
#include <cmath>
#include <algorithm>

std::vector<Bullet> BulletControl::bullets;

void BulletControl::moveBullets()
{
    for (unsigned i = 0; i < bullets.size(); i++){
        bullets[i].moveBullet();
        if(bullets[i].isDestroyed())
            bullets.erase(bullets.begin()+i);
    }
}

void BulletControl::drawBullets()
{
    for (auto& b : bullets)
        b.drawBullet();
}

void BulletControl::addBullet(Bullet &bullet)
{
    Intersection is;
    Position pos = is.checkIntersection(bullet.getStartingPosition(), bullet.getTarget(), Terrain::getCollisionLines());
    if (pos.x != -1 && pos.y != -1)
        bullet.setTarget(pos);
    bullet.setDirection(atan2(
        bullet.getTarget().y-bullet.getStartingPosition().y, 
        bullet.getTarget().x-bullet.getStartingPosition().x
    ));
    bullets.push_back(bullet);
}