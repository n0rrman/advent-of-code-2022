#include <fstream>
#include <iostream>

#include "Rope.h"
#include "Knot.h"

using namespace std;

int main()
{
    ifstream input_stream;
    input_stream.open("input.txt");

    Knot *knots[9];
    knots[8] = new Knot();
    for (int i = 8; i > 0; i--)
    {
        knots[i - 1] = new Knot(knots[i]);
    }
    Rope *rope = new Rope(knots[0], 1000, 1000);

    string line;
    while (getline(input_stream, line, '\n'))
    {
        const char direction = line[0];
        const int iterations = stoi(line.substr(2));

        switch (direction)
        {
        case 'U':
            for (size_t i = 0; i < iterations; i++)
                rope->moveUp();
            break;
        case 'L':
            for (size_t i = 0; i < iterations; i++)
                rope->moveLeft();
            break;
        case 'D':
            for (size_t i = 0; i < iterations; i++)
                rope->moveDown();
            break;
        case 'R':
            for (size_t i = 0; i < iterations; i++)
                rope->moveRight();
            break;
        }
    }

    const int resultsOne = knots[0]->getVisited().size();
    const int resultsTwo = knots[8]->getVisited().size();

    printf("\nPart one: %d\nPart two: %d\n", resultsOne, resultsTwo);

    return 0;
}
