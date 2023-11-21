#include <iostream>

#include "Knot.h"

using namespace std;

Knot::Knot()
{
    Knot(nullptr);
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
}

std::unordered_set<std::string> &Knot::getVisited()
{
    return visited;
}

Knot *Knot::getLastKnot()
{
    if (tailKnot != NULL)
    {
        return tailKnot->getLastKnot();
    }
    else
    {
        return this;
    }
}

void Knot::visit(const int &x, const int &y)
{
    visited.insert(to_string(x) + to_string(y));
}

void Knot::follow(const int &fromX, const int &fromY, const int &toX, const int &toY)
{

    bool xCheck = abs(toX - x) > ROPE_LENGTH;
    bool yCheck = abs(toY - y) > ROPE_LENGTH;

    if (xCheck | yCheck)
    {
        x = fromX;
        y = fromY;

        visit(x, y);
    }
}