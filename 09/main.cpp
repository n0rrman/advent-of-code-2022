// #include <algorithm>
#include <fstream>
#include <iostream>
// #include <functional>

#include "Rope.h"
#include "Knot.h"

using namespace std;

int main()
{
    ifstream input_stream;
    input_stream.open("test_input.txt");
    Knot knotOne = Knot();
    Rope rope = Rope(&knotOne, 0, 0);

    string line;
    while (getline(input_stream, line, '\n'))
    {
        const char direction = line[0];
        const int iterations = stoi(line.substr(2));

        switch (direction)
        {
        case 'U':
            for (size_t i = 0; i < iterations; i++)
                rope.moveUp();
            break;
        case 'L':
            for (size_t i = 0; i < iterations; i++)
                rope.moveLeft();
            break;
        case 'D':
            for (size_t i = 0; i < iterations; i++)
                rope.moveDown();
            break;
        case 'R':
            for (size_t i = 0; i < iterations; i++)
                rope.moveRight();
            break;
        }
    }

    const int resultsOne = rope.getTail()->getVisited().size();
    const int resultsTwo = knotOne.getVisited().size();

    printf("\nPart one: %d\nPart two: %d\n", resultsOne, resultsTwo);

    return 0;
}
