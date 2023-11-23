#include <iostream>
#include <vector>

#include "Monkey.h"

using namespace std;

Monkey::Monkey(
    vector<BigInteger> startingItems,
    function<BigInteger(BigInteger)> opFunc,
    unsigned int testDevisor)
{
    items = startingItems;
    inspectedItems = 0;

    operation = opFunc;
    devisor = testDevisor;
    stressReducer = 0;
}

void Monkey::connect(Monkey *trueMonkey, Monkey *falseMonkey)
{
    tMonkey = trueMonkey;
    fMonkey = falseMonkey;
}

void Monkey::processItem(BigInteger item)
{
    inspectedItems++;

    BigInteger newWorryLvl;
    newWorryLvl = operation(item) % stressReducer;
    newWorryLvl = worryControl(newWorryLvl);

    if ((newWorryLvl % devisor) == 0)
    {
        tMonkey->catchThrow(newWorryLvl);
    }
    else
    {
        fMonkey->catchThrow(newWorryLvl);
    }
}

void Monkey::inspectItems()
{
    BigInteger selectedItem;

    while (items.size() > 0)
    {
        selectedItem = items.front();
        items.erase(items.cbegin());

        processItem(selectedItem);
    }
}

unsigned int Monkey::getInspectedAmount()
{
    return inspectedItems;
}

void Monkey::catchThrow(BigInteger item)
{
    items.push_back(item);
}

void Monkey::setWorryControl(function<BigInteger(BigInteger)> func)
{
    worryControl = func;
}

unsigned int Monkey::getTestDevisor()
{
    return devisor;
}

void Monkey::addModReducer(unsigned int modReducer)
{
    stressReducer = modReducer;
}