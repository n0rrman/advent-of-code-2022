#ifndef KNOT_H
#define KNOT_H

#include <unordered_set>
#include <string>

#define ROPE_LENGTH 1

class Knot
{
public:
    Knot();
    Knot(Knot *knot);
    Knot *tailKnot;

    void setStart(const int &startX, const int &startY);
    void follow(const int &fromX, const int &fromY, const int &toX, const int &toY);

    std::unordered_set<std::string> &getVisited();
    Knot *getLastKnot();

    std::unordered_set<std::string> visited;

private:
    int x;
    int y;

    void visit(const int &x, const int &y);
};

#endif