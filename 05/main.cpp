#include <algorithm>
#include <fstream>
#include <sstream>
#include <stack>
#include <regex>

using namespace std;

void initStacks(deque<char> (&stacks)[9])
{
    ifstream input_stream;
    input_stream.open("initial_stacks.txt");

    string line;
    while (getline(input_stream, line, '\n'))
    {
        char lineChar;
        for (size_t i = 0; i < 9; i++)
        {
            lineChar = line[1 + (4 * i)];
            if ((lineChar >= 'A') && (lineChar <= 'Z'))
            {
                stacks[i].push_back(lineChar);
            }
        }
    }
}

void moveCrates(deque<char> (&stacks)[9], const size_t repetition, const size_t from, const size_t to)
{
    {
        for (size_t i = 0; i < repetition; i++)
        {
            stacks[to - 1].push_front(stacks[from - 1].front());
            stacks[from - 1].pop_front();
        }
    }
}

void moveMultipleCrates(deque<char> (&stacks)[9], const size_t repetition, const size_t from, const size_t to)
{
    char temp[repetition];
    {
        for (size_t i = 0; i < repetition; i++)
        {
            temp[i] = stacks[from - 1].front();
            stacks[from - 1].pop_front();
        }
        for (size_t i = 1; i <= repetition; i++)
        {
            stacks[to - 1].push_front(temp[repetition - i]);
        }
    }
}

void printResults(const string title, deque<char> (&stacks)[9])
{
    printf("%s: ", title.c_str());
    for (size_t i = 0; i < 9; i++)
    {
        printf("%c", stacks[i].front());
    }
    printf("\n");
}

int main()
{
    ifstream input_stream;
    input_stream.open("input.txt");

    deque<char> stacksPartOne[9];
    deque<char> stacksPartTwo[9];

    initStacks(stacksPartOne);
    initStacks(stacksPartTwo);

    string line;
    while (getline(input_stream, line, '\n'))
    {
        stringstream ss(line);
        string innerString;
        int params[3];
        size_t index = 0;

        while (getline(ss, innerString, ' '))
        {

            if (regex_match(innerString, regex("[0-9]$|^[1-9][0-9]")))
            {
                params[index] = stoi(innerString);
                index++;
            }
        }
        moveCrates(stacksPartOne, params[0], params[1], params[2]);
        moveMultipleCrates(stacksPartTwo, params[0], params[1], params[2]);
    }

    printResults("Part One", stacksPartOne);
    printResults("Part two", stacksPartTwo);

    return 0;
}
