#include <algorithm>
#include <iostream>
#include "Controls.h"
#include "Position.h"
#include "Player.h"

Position Controls::mousePosition = {0, 0};

std::vector<char> Controls::keysPressed;

void Controls::mouseFunction(int x, int y)
{
    mousePosition.x = x;
    mousePosition.y = y;
    glutPostRedisplay();
}

void Controls::keyboardFunction(unsigned char Key, int x, int y)
{
    if (std::find(keysPressed.begin(), keysPressed.end(), Key) == keysPressed.end())
    {
        keysPressed.push_back(Key);
    }
    Player::move();
}

void Controls::keyboardUpFunction(unsigned char Key, int x, int y)
{
    auto it = std::find(keysPressed.begin(), keysPressed.end(), Key);
    if (it != keysPressed.end())
    {
        keysPressed.erase(it);
    }
}