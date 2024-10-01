#include <iostream>
#include <fstream>

#include "Packet.h"

using namespace std;

int main()
{
    ifstream input_stream;
    input_stream.open("input.txt");

    string line;
    unsigned int index = 0;
    unsigned int partOne = 0;

    while (getline(input_stream, line, '\n'))
    {
        Packet p1 = Packet(line);
        getline(input_stream, line, '\n');
        Packet p2 = Packet(line);

        index++;

        if (index == 64)
        {
            cout << "diff: " << endl;
            cout << p1.toString() << endl;
            cout << p2.toString() << endl;
        }

        if (index == 96)
        {
            cout << "diff: " << endl;
            cout << p1.toString() << endl;
            cout << p2.toString() << endl;
        }

        // right order
        if (p1 < p2)
        {
            partOne += index;
            cout << "" << index << endl;
        }

        // empty line
        getline(input_stream, line, '\n');
    }

    int partTwo = 0;

    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    return 0;
}
