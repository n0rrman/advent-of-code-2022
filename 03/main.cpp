#include <algorithm>
#include <fstream>
#include <unordered_set>

using namespace std;

bool searchInventory(unordered_set<char> &inventory, char &item)
{
    unordered_set<char>::const_iterator search = inventory.find(item);

    if (search == inventory.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void buildSet(string &inventoryString, unordered_set<char> &inventorySet)
{
    size_t invLength = inventoryString.size();

    for (size_t i = 0; i < invLength; i++)
    {
        inventorySet.insert(inventoryString[i]);
    }
}

void findItemOne(string &inventory, char &item)
{
    int length = inventory.size();
    string subString = inventory.substr(length / 2);
    unordered_set<char> compartment;

    buildSet(subString, compartment);

    for (int i = 0; i < length / 2; i++)
    {
        if (searchInventory(compartment, inventory[i]))
        {
            item = inventory[i];
            return;
        }
    }
}

void findItemTwo(string (&lines)[3], char &item)
{
    int length = lines[0].size();
    unordered_set<char> searchSet[2];

    buildSet(lines[1], searchSet[0]);
    buildSet(lines[2], searchSet[1]);

    for (int i = 0; i < length; i++)
    {
        char searchItem = lines[0][i];
        if (searchInventory(searchSet[0], searchItem) && searchInventory(searchSet[1], searchItem))
        {
            item = searchItem;
            return;
        }
    }
}

int getCharValue(char character)
{
    int value = (int)character - 96;
    return value > 0 ? value : value + 58;
}

int main()
{
    ifstream input_stream;
    input_stream.open("input.txt");

    int partOne = 0;
    int partTwo = 0;
    string line;

    // Part two
    int index = 0;
    string lines[3];

    while (getline(input_stream, line, '\n'))
    {
        char commonItemOne;
        char commonItemTwo;

        // Part One
        findItemOne(line, commonItemOne);
        partOne += getCharValue(commonItemOne);

        // Part Two
        lines[index] = line;
        index++;
        if (index == 3)
        {
            findItemTwo(lines, commonItemTwo);
            partTwo += getCharValue(commonItemTwo);
            index = 0;
        }
    }

    printf("\nPart one: %d\n", partOne);
    printf("Part two: %d\n\n", partTwo);

    return 0;
}
