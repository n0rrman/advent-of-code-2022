#include <iostream>
#include <fstream>

using namespace std;

typedef vector<vector<char>> Map;

struct Coords
{
    unsigned int x, y, nextX, nextY;
};

bool isValidMove(Map &map, pair<unsigned int, unsigned int> fromCoords, pair<unsigned int, unsigned int> toCoords)
{
    if ((toCoords.first < 0) || (toCoords.second < 0))
        return false;

    if (map[0].size() <= toCoords.first || map.size() <= toCoords.second)
        return false;

    char fromElevation = map[fromCoords.second][fromCoords.first];
    char toElevation = map[toCoords.second][toCoords.first];
    if ((abs(toElevation - fromElevation) > 1) && (fromElevation < toElevation))
        return false;

    return true;
}

int findEnd(Map &map, pair<unsigned int, unsigned int> &startCoords, pair<unsigned int, unsigned int> &endCoords, unsigned int part)
{
    unsigned int fromX, fromY;
    unsigned int nextX, nextY;
    vector<vector<int>> distanceMap(map.size(), vector<int>(map[0].size(), INT_MAX));
    vector<Coords> workList;

    if (isValidMove(map, {startCoords.first, startCoords.second}, {startCoords.first + 1, startCoords.second}))
        workList.push_back({startCoords.first, startCoords.second, startCoords.first + 1, startCoords.second});
    if (isValidMove(map, {startCoords.first, startCoords.second}, {startCoords.first - 1, startCoords.second}))
        workList.push_back({startCoords.first, startCoords.second, startCoords.first - 1, startCoords.second});
    if (isValidMove(map, {startCoords.first, startCoords.second}, {startCoords.first, startCoords.second + 1}))
        workList.push_back({startCoords.first, startCoords.second, startCoords.first, startCoords.second + 1});
    if (isValidMove(map, {startCoords.first, startCoords.second}, {startCoords.first, startCoords.second - 1}))
        workList.push_back({startCoords.first, startCoords.second, startCoords.first, startCoords.second - 1});

    distanceMap[startCoords.second][startCoords.first] = 0;

    unsigned int newDistance;
    while (!workList.empty())
    {
        fromX = workList.front().x;
        fromY = workList.front().y;
        nextX = workList.front().nextX;
        nextY = workList.front().nextY;

        workList.erase(workList.begin());

        if ((1 + distanceMap[fromY][fromX]) < distanceMap[nextY][nextX])
        {
            distanceMap[nextY][nextX] = distanceMap[fromY][fromX] + 1;

            if ((part == 2) && (map[nextY][nextX] == 'a'))
                distanceMap[nextY][nextX] = 0;

            if (isValidMove(map, {nextX, nextY}, {nextX + 1, nextY}))
                workList.push_back({nextX, nextY, nextX + 1, nextY});
            if (isValidMove(map, {nextX, nextY}, {nextX - 1, nextY}))
                workList.push_back({nextX, nextY, nextX - 1, nextY});
            if (isValidMove(map, {nextX, nextY}, {nextX, nextY + 1}))
                workList.push_back({nextX, nextY, nextX, nextY + 1});
            if (isValidMove(map, {nextX, nextY}, {nextX, nextY - 1}))
                workList.push_back({nextX, nextY, nextX, nextY - 1});
        }
    }

    return distanceMap[endCoords.second][endCoords.first];
}

int main()
{
    ifstream input_stream;
    input_stream.open("input.txt");

    Map signalMap;
    pair<unsigned int, unsigned int> startXY;
    pair<unsigned int, unsigned int> endXY;

    unsigned int x;
    unsigned int y = 0;
    string line;
    while (getline(input_stream, line, '\n'))
    {
        x = 0;
        signalMap.push_back(vector<char>());
        for (char &c : line)
        {
            if (c == 'S')
            {
                startXY = {x, y};
                signalMap[y].push_back('a');
            }
            else if (c == 'E')
            {
                endXY = {x, y};
                signalMap[y].push_back('z');
            }
            else
            {
                signalMap[y].push_back(c);
            }
            x++;
        }
        y++;
    }
    int partOne = findEnd(signalMap, startXY, endXY, 1);
    int partTwo = findEnd(signalMap, startXY, endXY, 2);

    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    return 0;
}
