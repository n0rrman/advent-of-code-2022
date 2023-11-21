#include <iostream>

#include "Rope.h"

using namespace std;

Rope::Rope(Knot *knot, const int startX, const int startY)
{
    tailKnot = knot;
    tailKnot->setStart(startX, startY);

    x = startX;
    y = startY;
};

void Rope::moveUp()
{
    y++;
    tailKnot->follow(x, y - 1, x, y);
};

void Rope::moveRight()
{
    x++;
    tailKnot->follow(x - 1, y, x, y);
};

void Rope::moveDown()
{
    y--;
    tailKnot->follow(x, y + 1, x, y);
};

void Rope::moveLeft()
{
    x--;
    tailKnot->follow(x + 1, y, x, y);
};
