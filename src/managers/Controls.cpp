#include <algorithm>
#include <iostream>
#include "Controls.h"
#include "Position.h"
#include "Player.h"

Position Controls::mousePosition = {0, 0};

std::vector<char> Controls::keysPressed;

void Controls::mouseMove(int x, int y)
{
    std::cout << x << " " << y << std::endl;
    mousePosition.x = x;
    mousePosition.y = y;
    glutPostRedisplay();
}

void Controls::mouseClick(int button, int state, int x, int y) {
    if(state == GLUT_DOWN)
        if(button == GLUT_LEFT_BUTTON)
            Player::shoot(mousePosition);
}

void Controls::drawAim() {
    int distance = 5;
    int length = 15;

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(mousePosition.x+distance, mousePosition.y);
    glVertex2f(mousePosition.x+length, mousePosition.y);

    glVertex2f(mousePosition.x-distance, mousePosition.y);
    glVertex2f(mousePosition.x-length, mousePosition.y);
    
    glVertex2f(mousePosition.x, mousePosition.y+distance);
    glVertex2f(mousePosition.x, mousePosition.y+length);
    
    glVertex2f(mousePosition.x, mousePosition.y-distance);
    glVertex2f(mousePosition.x, mousePosition.y-length);
    glEnd();
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