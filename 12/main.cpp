#include <iostream>
#include <fstream>

using namespace std;

typedef vector<vector<char>> Map;

struct Coords
{
    unsigned int x, y, nextX, nextY;
};

bool isValidMove(Map &map, vector<Coords> &workList, pair<unsigned int, unsigned int> fromCoords, pair<unsigned int, unsigned int> toCoords)
{
    // auto it = find_if(workList.begin(), workList.end(), [&](const Coords &set)
    //                   { return set.x == fromCoords.first && set.y == fromCoords.second && set.nextX == toCoords.first && set.nextY == toCoords.second; });

    // if (it != workList.end())
    // {
    //     return false;
    // }

    if ((toCoords.first < 0) || (toCoords.second < 0))
        return false;

    if (map[0].size() <= toCoords.first || map.size() <= toCoords.second)
        return false;

    //    if (distanceMap[toCoords.second][toCoords.second] != INT_MAX)
    //      return false;
    // cout << "testc" << endl;
    char prevElevation = map[fromCoords.second][fromCoords.first];
    char currentElevation = map[toCoords.second][toCoords.first];
    // if ((map[y][x] == 'S') && ((map[prevY][prevX] == 'b') || (map[prevY][prevX] == 'a')))
    // {
    //     cout << "end found" << endl;
    //     return true;
    // }
    // if (!((1 + currentElevation) <= prevElevation))
    if ((abs(currentElevation - prevElevation) > 1) && (prevElevation < currentElevation))
    {
        return false;
    }
    return true;
}

int findEnd(Map &map, pair<unsigned int, unsigned int> &startCoords, pair<unsigned int, unsigned int> &endCoords)
{
    unsigned int fromX, fromY;
    unsigned int nextX, nextY;
    vector<vector<int>> distanceMap(map.size(), vector<int>(map[0].size(), INT_MAX));
    vector<Coords> workList;

    if (isValidMove(map, workList, {startCoords.first, startCoords.second}, {startCoords.first + 1, startCoords.second}))
        workList.push_back({startCoords.first, startCoords.second, startCoords.first + 1, startCoords.second});
    if (isValidMove(map, workList, {startCoords.first, startCoords.second}, {startCoords.first - 1, startCoords.second}))
        workList.push_back({startCoords.first, startCoords.second, startCoords.first - 1, startCoords.second});
    if (isValidMove(map, workList, {startCoords.first, startCoords.second}, {startCoords.first, startCoords.second + 1}))
        workList.push_back({startCoords.first, startCoords.second, startCoords.first, startCoords.second + 1});
    if (isValidMove(map, workList, {startCoords.first, startCoords.second}, {startCoords.first, startCoords.second - 1}))
        workList.push_back({startCoords.first, startCoords.second, startCoords.first, startCoords.second - 1});

    distanceMap[startCoords.second][startCoords.first] = 0;

    unsigned int newDistance;
    while (!workList.empty())
    {

        fromX = workList.front().x;
        fromY = workList.front().y;
        nextX = workList.front().nextX;
        nextY = workList.front().nextY;

        if (map[fromY][fromX] == 'w')
            cout << "AIHSDIASDHA" << endl;

        map[fromY][fromX] = 'X';

        cout << "from: " << fromX << ", " << fromY << endl;
        cout << "next: " << nextX << ", " << nextY << endl;

        workList.erase(workList.begin());

        if (map[fromY][fromX] == 'a')
            distanceMap[fromY][fromX] = 0;

        if ((1 + distanceMap[fromY][fromX]) < distanceMap[nextY][nextX])
        {
            distanceMap[nextY][nextX] = distanceMap[fromY][fromX] + 1;

            if (isValidMove(map, workList, {nextX, nextY}, {nextX + 1, nextY}))
                workList.push_back({nextX, nextY, nextX + 1, nextY});
            if (isValidMove(map, workList, {nextX, nextY}, {nextX - 1, nextY}))
                workList.push_back({nextX, nextY, nextX - 1, nextY});
            if (isValidMove(map, workList, {nextX, nextY}, {nextX, nextY + 1}))
                workList.push_back({nextX, nextY, nextX, nextY + 1});
            if (isValidMove(map, workList, {nextX, nextY}, {nextX, nextY - 1}))
                workList.push_back({nextX, nextY, nextX, nextY - 1});
        }
    }
    cout << distanceMap.size() << " + " << distanceMap[0].size() << endl;

    return distanceMap[endCoords.second][endCoords.first];
}

int main()
{
    ifstream input_stream;

    input_stream.open("input.txt");

    string line;

    Map signalMap;
    pair<unsigned int, unsigned int> startXY;
    pair<unsigned int, unsigned int> endXY;

    unsigned int x;
    unsigned int y = 0;
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

    cout << startXY.second << ", " << startXY.first << " - " << signalMap[startXY.second][startXY.first] << endl;
    cout << endXY.second << ", " << endXY.first << " - " << signalMap[endXY.second][endXY.first] << endl;

    int test = findEnd(signalMap, startXY, endXY);

    for (vector<char> &row : signalMap)
    {

        for (char &e : row)
        {

            cout << e;
        }
        cout << endl;
    }
    // high_resolution_clock::time_point t2 = high_resolution_clock::now();
    // duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    // std::cout << "It took me " << time_span.count() << " seconds." << endl;

    cout << "Distance: " << test << endl;

    return 0;
}
