#include <algorithm>
#include <fstream>

using namespace std;

void splitString(string &input, int (&output)[4])
{
    size_t firstDelim = input.find('-') + 1;
    size_t middleDelim = input.find(',') + 1;
    size_t lastDelim = input.find_last_of('-') + 1;

    size_t delims[4] = {0, firstDelim, middleDelim, lastDelim};

    for (int i = 0; i < 4; i++)
    {
        size_t length = delims[i + 1] - delims[i] - 1;
        string substring = input.substr(delims[i], length);

        output[i] = stoi(substring);
    }
}

bool hasPartialOverlap(int (&data)[4])
{
    return ((data[0] <= data[3]) & (data[1] >= data[2])) | ((data[2] <= data[1]) & (data[3] >= data[0]));
}

bool hasFullOverlap(int (&data)[4])
{
    return ((data[0] <= data[2]) & (data[1] >= data[3])) | ((data[0] >= data[2]) & (data[1] <= data[3]));
}

int main()
{
    ifstream input_stream;
    input_stream.open("input.txt");

    int fullOverlapCounter = 0;
    int partialOverlapCounter = 0;

    string line;
    while (getline(input_stream, line, '\n'))
    {
        int input[4];

        splitString(line, input);

        fullOverlapCounter += hasFullOverlap(input) ? 1 : 0;
        partialOverlapCounter += hasPartialOverlap(input) ? 1 : 0;
    }

    printf("\nPart one: %d\n", fullOverlapCounter);
    printf("Part two: %d\n\n", partialOverlapCounter);

    return 0;
}
