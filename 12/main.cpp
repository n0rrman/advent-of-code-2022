#include <iostream>
#include <fstream>
#include <unordered_set>

#include <chrono>
#include <iostream>
#include <ctime>
#include <ratio>

using namespace std;
using namespace std::chrono;

typedef vector<vector<char>> Map;

bool isValidMove(Map &map, vector<pair<int, int>> &path, int x, int y)
{
    for (pair<int, int> &pair : path)
    {
        if ((x == pair.first) && (y == pair.second))
        {
            return false;
        }
    }

    if ((x < 0) || (y < 0))
    {
        return false;
    }
    if (map[0].size() <= x)
        return false;
    if (map.size() <= y)
        return false;

    int prevX = path.back().first;
    int prevY = path.back().second;
    char prevElevation = map[prevY][prevX];
    char currentElevation = map[y][x];
    if ((map[y][x] == 'S') && ((map[prevY][prevX] == 'b') || (map[prevY][prevX] == 'a')))
    {
        cout << "end found" << endl;
        return true;
    }
    if (abs(prevElevation - currentElevation) > 1)
    {
        return false;
    }

    return true;
}

unsigned int findE(Map &map, vector<pair<int, int>> path, int ttl, int x, int y)

{

    if (!isValidMove(map, path, x, y))
    {
        return 99999;
    }
    path.push_back({x, y});

    if (ttl <= 0)
    {
        return 99999;
    }

    if (map[y][x] == 'S')
    {

        cout << x << ", " << y << endl;
        return 1;
    }

    unsigned int newTTL = ttl - 1;

    return 1 + min({findE(map, path, newTTL, x - 1, y),
                    findE(map, path, newTTL, x, y - 1),
                    findE(map, path, newTTL, x + 1, y),
                    findE(map, path, newTTL, x, y + 1)});
}

int findEnd(Map &map)
{
    // int startX = 0;
    // int startX = 5;
    // int startY = 2;
    int startY = 20;
    int startX = 72;
    // int startY = 20;
    // int startY = 0;o
    cout << map.size() << endl;
    cout << map[startY][startX] << endl;
    map[startY][startX] = 'z';
    // map[startY][startX] = 'a';
    int TTL = 100;
    unsigned int a = UINT_MAX, b = UINT_MAX, c = UINT_MAX, d = UINT_MAX;

    vector<pair<int, int>> path;

    path.push_back({startX, startY});

    if (isValidMove(map, path, startX - 1, startY))
    {
        a = findE(map, path, TTL, startX - 1, startY);
    }
    if (isValidMove(map, path, startX, startY - 1))
    {
        b = findE(map, path, TTL, startX, startY - 1);
    }
    if (isValidMove(map, path, startX + 1, startY))
    {
        c = findE(map, path, TTL, startX + 1, startY);
    }
    if (isValidMove(map, path, startX, startY + 1))
    {
        d = findE(map, path, TTL, startX, startY + 1);
    }

    return 1 + min({a, b, c, d});
}

int main()
{
    ifstream input_stream;

    input_stream.open("input.txt");

    string line;

    Map signalMap;

    unsigned int y = 0;
    unsigned int x;

    while (getline(input_stream, line, '\n'))
    {
        x = 0;
        signalMap.push_back(vector<char>());

        for (char &c : line)
        {
            signalMap[y].push_back(c);
        }
        y++;
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    int test = findEnd(signalMap);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "It took me " << time_span.count() << " seconds." << endl;

    cout << test << endl;

    return 0;
}
