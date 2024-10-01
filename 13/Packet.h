#ifndef PACKET_H
#define PACKET_H

#include <string>

class Packet
{
public:
    Packet(std::string packetString);
    std::string toString();

    bool operator<(Packet &otherPacket);

private:
    std::string packet;

    bool getNextNumber(const std::string &packetString, int *index, int &nextInt);
};

#endif