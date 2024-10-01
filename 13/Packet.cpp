#include <algorithm>
#include <ctype.h>

#include <iostream>

#include "Packet.h"

using namespace std;

Packet::Packet(string packetString)
{
    packet = packetString;
}

string Packet::toString()
{
    return packet;
}

bool Packet::getNextNumber(const string &packetString, int *index, int &nextInt)
{
    nextInt = INT_MAX;
    size_t maxLength = packetString.length();

    char activeChar = '\0';
    char prevChar;

    while (!isdigit(activeChar))
    {
        if (*index >= maxLength)
        {
            return false;
        }
        prevChar = activeChar;
        activeChar = packetString.at(*index);
        *index += 1;
        if ((prevChar == '[') && (activeChar == ']'))
        {
            nextInt = -1;
            return true;
        }
    }

    int start = *index - 1;

    while (isdigit(activeChar))
    {
        if (*index >= maxLength)
        {
            return false;
        }
        activeChar = packetString.at(*index);
        *index += 1;
    }
    // cout << "\ttest: " << packetString.substr(start, *index - start - 1) << endl;
    nextInt = stoi(packetString.substr(start, *index - start - 1));
    return true;
}

bool Packet::operator<(Packet &otherPacket)
{
    const string otherPacketString = otherPacket.toString();

    int ownIndex = 0;
    int otherIndex = 0;

    int ownInt, otherInt;
    bool emptyVsEmpty = true;

    while (getNextNumber(packet, &ownIndex, ownInt) | getNextNumber(otherPacketString, &otherIndex, otherInt))
    {
        emptyVsEmpty = false;
        // cout << "own: " << ownInt << "\nother: " << otherInt << endl;
        if ((ownInt == -1) && (otherInt == -1))
        {
            cout << "this happened " << endl;
            ownInt = 0;
            otherInt = 0;
        }

        if (ownInt == INT_MAX)
        {
            return true;
        }

        if (ownInt == -1)
        {
            // cout << "does this happen?" << endl;
            return true;
        }

        if (otherInt == INT_MAX)
        {
            return false;
        }

        if (otherInt == -1)
        {
            // cout << "does this happen?" << endl;
            return false;
        }

        if (ownInt != otherInt)
        {
            return ownInt < otherInt;
        }
    }
    if (emptyVsEmpty)
        return otherPacketString.length() >= packet.length();

    return true;
}

// int helper(char &activeChar, size_t &level, size_t &index, string &packetString)
// {
//     int temp;
//     int activeInt = NULL;

//     // cout << "active: " << activeChar;
//     while ((activeInt != NULL) || packetString.length() < index)
//     {
//         switch (activeChar)
//         {
//         case '[':
//             level++;
//             index++;
//             break;
//         case ']':
//             level--;
//             index++;
//             break;
//         case ',':
//             index++;
//             break;
//         default:
//             temp = index;
//             while (isdigit(activeChar))
//             {
//                 activeChar = packetString.at(index);
//                 // cout << "char: " << activeChar;
//                 index++;
//             }

//             return stoi(packetString.substr(temp, index - temp));
//             // cout << "int: " << activeInt;
//         }
//         activeChar = packetString.at(index);
//     }
// }

// bool Packet::operator<(Packet &otherPacket)
// {
//     size_t ownLength = packet.length();
//     size_t otherLength = otherPacket.toString().length();

//     size_t ownIndex = 0;
//     size_t ownLevel = 0;
//     char activeOwnChar;
//     int activeOwnInt;

//     size_t otherIndex = 0;
//     size_t otherLevel = 0;
//     char activeOtherChar;
//     int activeOtherInt;

//     int temp;

//     while ((ownIndex < ownLength) && (otherIndex < otherLength))
//     {
//         activeOwnChar = packet.at(ownIndex);
//         activeOtherChar = otherPacket.toString().at(otherIndex);

//         // // activeOwnInt = helper(activeOwnChar, ownLevel, ownIndex, packet);

//         // string otherPacketString = otherPacket.toString();
//         // activeOtherInt = helper(activeOtherChar, otherLevel, otherIndex, otherPacketString);

//         // otherIndex++;

//         cout << "own: " << activeOwnInt << endl;
//         cout << "other: " << activeOtherInt << endl;
//     }

//     return ownLength < otherLength;
// }
