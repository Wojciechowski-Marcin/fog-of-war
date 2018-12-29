#ifndef CONTROLS_H
#define CONTROLS_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include "Position.h"

class Controls
{
  private:
    static Position mousePosition;
  public:
    void drawAim();
    static std::vector<char> keysPressed;
    static void mouseMove(int x, int y);
    static void mouseClick(int button, int state, int x, int y);
    static void keyboardFunction(unsigned char Key, int x, int y);
    static void keyboardUpFunction(unsigned char Key, int x, int y);
};

#endif