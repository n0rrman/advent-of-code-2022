#include <algorithm>
#include <fstream>

using namespace std;

void getPartOnePoints(char &a, char &b, int &point)
{
    switch (b)
    {
    case 'X':
        point += 1;
        switch (a)
        {
        case 'A':
            point += 3;
            return;
        case 'B':
            point += 0;
            return;
        case 'C':
            point += 6;
            return;
        }
    case 'Y':
        point += 2;
        switch (a)
        {
        case 'A':
            point += 6;
            return;
        case 'B':
            point += 3;
            return;
        case 'C':
            point += 0;
            return;
        }
    case 'Z':
        point += 3;
        switch (a)
        {
        case 'A':
            point += 0;
            return;
        case 'B':
            point += 6;
            return;
        case 'C':
            point += 3;
            return;
        }
    }
}

void getPartTwoPoints(char &a, char &b, int &point)
{
    switch (b)
    {
    case 'X':
        point += 0;
        switch (a)
        {
        case 'A':
            point += 3;
            return;
        case 'B':
            point += 1;
            return;
        case 'C':
            point += 2;
            return;
        }
    case 'Y':
        point += 3;
        switch (a)
        {
        case 'A':
            point += 1;
            return;
        case 'B':
            point += 2;
            return;
        case 'C':
            point += 3;
            return;
        }
    case 'Z':
        point += 6;
        switch (a)
        {
        case 'A':
            point += 2;
            return;
        case 'B':
            point += 3;
            return;
        case 'C':
            point += 1;
            return;
        }
    }
}

int main()
{
    ifstream input_stream;
    input_stream.open("input.txt");

    int partOne = 0;
    int partTwo = 0;
    string line;

    while (getline(input_stream, line, '\n'))
    {
        char elf = line[0];
        char shape = line[2];

        getPartOnePoints(elf, shape, partOne);
        getPartTwoPoints(elf, shape, partTwo);
    }

    printf("\nPart one: %d\n", partOne);
    printf("Part two: %d\n\n", partTwo);

    return 0;
}