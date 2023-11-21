#include <iostream>

#include "Knot.h"

using namespace std;

Knot::Knot()
{
    tailKnot = nullptr;
}

Knot::Knot(Knot *knot)
{
    tailKnot = knot;
}

void Knot::setStart(const int &startX, const int &startY)
{
    x = startX;
    y = startY;

    visit(x, y);

    if (tailKnot != nullptr)
    {
        tailKnot->setStart(startX, startY);
    }
}

std::unordered_set<std::string> &Knot::getVisited()
{
    return visited;
}

void Knot::visit(const int &x, const int &y)
{
    visited.insert(to_string(x) + to_string(y));
}

void Knot::follow(const int &fromX, const int &fromY, const int &toX, const int &toY)
{
    bool xCheck = abs(toX - x) > ROPE_LENGTH;
    bool yCheck = abs(toY - y) > ROPE_LENGTH;

    int oldX = x;
    int oldY = y;

    if (xCheck | yCheck)
    {
        x += (toX > x) - (toX < x);
        y += (toY > y) - (toY < y);
    }

    if (tailKnot != nullptr)
    {
        tailKnot->follow(oldX, oldY, x, y);
    }
    visit(x, y);
}