#include <algorithm>
#include <fstream>
#include <unordered_set>

using namespace std;

template <size_t N>
void populateArray(char (&memory)[N])
{
    for (size_t i = 0; i < N - 1; i++)
    {
        memory[i] = memory[N - 1];
    }
}

template <size_t N>
bool checkUnique(const char (&chars)[N])
{
    unordered_set<char> set(begin(chars), end(chars));
    return set.size() == N;
}

int main()
{
    ifstream inputStream;
    inputStream.open("input.txt");

    char inputChar;
    char memoryOne[4];
    char memoryTwo[14];

    bool partOneDone = false;
    bool partTwoDone = false;

    size_t index = 0;
    while (inputStream.get(inputChar) && !(partOneDone & partTwoDone))
    {
        index++;
        memoryOne[3] = inputChar;
        memoryTwo[13] = inputChar;
        if (index == 1)
        {
            populateArray(memoryOne);
            populateArray(memoryTwo);
        }

        if (checkUnique(memoryOne) & !partOneDone)
        {
            printf("Part one: %d\n", (int)index);
            partOneDone = true;
        }

        if (checkUnique(memoryTwo) & !partTwoDone)
        {
            printf("Part two: %d\n", (int)index);
            partTwoDone = true;
        }

        memoryOne[index % 3] = memoryOne[3];
        memoryTwo[index % 13] = memoryTwo[13];
    }

    return 0;
}