#ifndef SYSTEMSTORAGE_H
#define SYSTEMSTORAGE_H
#include <iostream>
#include <cmath>
#include "MMU.h"
using namespace std;

class PhysicalPageNode; // this type of starage only acccepts physical

class SystemDisk
{
public:
    static const int systemMemorySize = 8096; // GB
    static const int swapMemorySize = 4096;   // GB
    int swapMemoryLeft;
    ///// build the arrays representing memory partition

    PhysicalPageNode swapMemory[swapMemorySize];

    SystemDisk()
    {
        delay(3);
        cout << "Freeing up swap memory..." << endl;
        this->swapMemoryLeft = 4096;
        delay(3);
        cout << "Available swap memory: " << swapMemoryLeft << endl;
        delay(3);
        cout << "Swap memory ready to be used!" << endl;
    }
};

#endif