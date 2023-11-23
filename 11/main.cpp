#include <fstream>
#include <iostream>
#include <numeric>

#include "Monkey.h"

using namespace std;

template <int N>
BigInteger getMonkeyBusiness(Monkey *monkeyList[N])
{
    BigInteger amount;
    BigInteger highestInspect = 0;
    BigInteger secondHighest = 0;

    for (int i = 0; i < N; i++)
    {
        amount = monkeyList[i]->getInspectedAmount();
        if (amount > highestInspect)
        {
            BigInteger temp = amount;
            amount = highestInspect;
            highestInspect = temp;
        }

        if (amount > secondHighest)
            secondHighest = amount;
    }

    return highestInspect * secondHighest;
}

void initMonkeys(Monkey *monkey[8])
{
    monkey[0] = new Monkey(
        vector<BigInteger>{72, 97},
        [](BigInteger x)
        { return x * 13; },
        19);

    monkey[1] = new Monkey(
        vector<BigInteger>{55, 70, 90, 74, 95},
        [](BigInteger x)
        { return x * x; },
        7);

    monkey[2] = new Monkey(
        vector<BigInteger>{74, 97, 66, 57},
        [](BigInteger x)
        { return x + 6; },
        17);

    monkey[3] = new Monkey(
        vector<BigInteger>{86, 54, 53},
        [](BigInteger x)
        { return x + 2; },
        13);

    monkey[4] = new Monkey(
        vector<BigInteger>{50, 65, 78, 50, 62, 99},
        [](BigInteger x)
        { return x + 3; },
        11);

    monkey[5] = new Monkey(
        vector<BigInteger>{90},
        [](BigInteger x)
        { return x + 4; },
        2);

    monkey[6] = new Monkey(
        vector<BigInteger>{88, 92, 63, 94, 96, 82, 53, 53},
        [](BigInteger x)
        { return x + 8; },
        5);

    monkey[7] = new Monkey(
        vector<BigInteger>{70, 60, 71, 69, 77, 70, 98},
        [](BigInteger x)
        { return x * 7; },
        3);

    monkey[0]->connect(monkey[5], monkey[6]);
    monkey[1]->connect(monkey[5], monkey[0]);
    monkey[2]->connect(monkey[1], monkey[0]);
    monkey[3]->connect(monkey[1], monkey[2]);
    monkey[4]->connect(monkey[3], monkey[7]);
    monkey[5]->connect(monkey[4], monkey[6]);
    monkey[6]->connect(monkey[4], monkey[7]);
    monkey[7]->connect(monkey[2], monkey[3]);
}

template <int N>
void setWorryControls(Monkey *monkey[N], function<BigInteger(BigInteger)> worryControl)
{
    for (int i = 0; i < N; i++)
    {
        monkey[i]->setWorryControl(worryControl);
    }
}

template <int N>
void addModReducers(Monkey *monkeys[N], unsigned int modReducer)
{
    for (int i = 0; i < N; i++)
    {
        monkeys[i]->addModReducer(modReducer);
    }
}

template <int N>
void runMonkeyGang(Monkey *monkeys[N], const int rounds)
{
    for (int r = 0; r < rounds; r++)
    {
        for (int i = 0; i < N; i++)
        {
            monkeys[i]->inspectItems();
        }
    }
}

int main()
{
    const int monkeyCount = 8;
    Monkey *monkeyGang[monkeyCount];

    // Part one:
    unsigned int partOne;
    initMonkeys(monkeyGang);
    setWorryControls<monkeyCount>(monkeyGang, [](int x)
                                  { return x / 3; });
    addModReducers<monkeyCount>(monkeyGang, 0);

    runMonkeyGang<monkeyCount>(monkeyGang, 20);
    partOne = getMonkeyBusiness<monkeyCount>(monkeyGang);

    cout << "Part one: " << partOne << endl;

    // Part two:
    BigInteger partTwo;
    initMonkeys(monkeyGang);
    setWorryControls<monkeyCount>(monkeyGang, [](int x)
                                  { return x; });

    BigInteger lcm = 1;
    for (int i = 0; i < monkeyCount; i++)
    {
        lcm *= monkeyGang[i]->getTestDevisor();
    }
    addModReducers<monkeyCount>(monkeyGang, lcm);

    runMonkeyGang<monkeyCount>(monkeyGang, 10000);
    partTwo = getMonkeyBusiness<monkeyCount>(monkeyGang);

    cout << "Part two: " << partTwo << endl;

    return 0;
}
