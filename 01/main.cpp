#include <algorithm>
#include <fstream>

using namespace std;

void calcSum(const int (&array)[3], int &result)
{
    for (size_t i = 0; i < 3; ++i)
    {
        result += array[i];
    }
}

int main()
{
    ifstream input_stream;
    input_stream.open("input.txt");

    string line;
    int sum = 0;

    // Part one
    int maxVal = 0;

    // Part two
    int maxVals[3] = {0, 0, 0};
    int maxValsSum;

    while (getline(input_stream, line, '\n'))
    {
        try
        {
            int val = stoi(line);
            sum += val;
        }
        catch (...)
        {
            // Part one
            maxVal = maxVal > sum ? maxVal : sum;

            // Part two
            maxVals[0] = maxVals[0] > sum ? maxVals[0] : sum;
            sort(maxVals, maxVals + 3);

            sum = 0;
        }
    }

    calcSum(maxVals, maxValsSum);

    printf("\nPart one: %d\n", maxVal);
    printf("Part two: %d\n\n", maxValsSum);

    return 0;
}