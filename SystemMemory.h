#ifndef SYSTEMMEMORY_H
#define SYSTEMMEMORY_H
#include <iostream>
#include <cmath>
#include "Delays.h"
#include <queue>
#include <stdexcept>
using namespace std;
// class PhysicalPageNode;
// class VirtualPageNode;

class PhysicalPageNode
{
public:
    int size = 1; // GB
    bool inRAM = false;
    int myIndex;
    string myData = "data";
};

class VirtualPageNode
{
public:
    int size = 1; // GB
    int inTLB;    // to determine if its in the buffer inside the mmu
    int myIndex;  // determine its index in ram or disk
};

struct PageTableEntryInstance
{
    VirtualPageNode VPN;
    PhysicalPageNode PPN;
};

class SystemMemory
{
public:
    int totalFrames = 8;        // Total frames in memory
    std::queue<int> freeFrames; // Queue of free frames

    // Constructor to initialize free frames
    SystemMemory()
    {
        for (int i = 0; i < totalFrames; ++i)
        {
            freeFrames.push(i);
        }
    }

    // Allocate a frame
    int allocateFrame()
    {
        if (freeFrames.empty())
        {
            throw std::runtime_error("No free frames available!");
        }
        int frame = freeFrames.front();
        freeFrames.pop();
        std::cout << "Allocated Frame: " << frame << std::endl;
        return frame;
    }

    // Free a frame
    void freeFrame(int frameNumber)
    {
        freeFrames.push(frameNumber);
        std::cout << "Freed Frame: " << frameNumber << std::endl;
    }
};

class PageTable
{
public:
    static const int size = 64; // each process will be able to keep 64Mb of ram, entire sistem has 256
    int pagesLeft = 64;         // keep modifyin or updating
    PageTableEntryInstance PT[size];

    // PageTable(int pages)
    // {
    //     this->size = pages;
    //     this->pagesLeft = pages;
    // };
};

#endif