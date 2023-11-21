#ifndef ROPE_H
#define ROPE_H

#include <unordered_set>
#include <string>

#include "Knot.h"

class Rope
{
public:
    Rope(Knot *knot, const int startX, const int startY);

    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();

private:
    Knot *tailKnot;

    int x;
    int y;
};

#endif