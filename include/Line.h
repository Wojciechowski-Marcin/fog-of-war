#ifndef LINE_H
#define LINE_H

#include "Position.h"

struct Line
{
    Position a;
    Position b;
    bool operator==(const Line& l)
    {
        return a == l.a && b == l.b;
    }
};

#endif