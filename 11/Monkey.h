#ifndef MONKEY_H
#define MONKEY_H

#include <vector>
#include <functional>

using BigInteger = unsigned long int;

class Monkey
{
public:
    Monkey(
        std::vector<BigInteger> startingItems,
        std::function<BigInteger(BigInteger)> opFunc,
        unsigned int testDevisor);

    void connect(Monkey *trueMonkey,
                 Monkey *falseMonkey);

    void inspectItems();
    void processItem(BigInteger item);
    void setWorryControl(std::function<BigInteger(BigInteger)> func);
    void catchThrow(BigInteger item);
    void addModReducer(unsigned int modReducer);

    unsigned int getInspectedAmount();
    unsigned int getTestDevisor();

private:
    std::vector<BigInteger> items;

    std::function<BigInteger(BigInteger)> operation;
    std::function<BigInteger(BigInteger)> worryControl;

    unsigned int inspectedItems;
    unsigned int devisor;
    unsigned int stressReducer;

    Monkey *tMonkey;
    Monkey *fMonkey;
};

#endif