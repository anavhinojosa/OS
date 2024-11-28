#ifndef MMU_H
#define MMU_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include "SystemMemory.h"
#include "SystemStorage.h"

using namespace std;

struct MMUPageTableEntry {
    int frameNumber;
    bool valid;
};

class MMUPageTable {
public:
    unordered_map<int, MMUPageTableEntry> table;
    queue<int> lruQueue; // for LRU replacement
    int totalFrames;

    MMUPageTable(int frames) : totalFrames(frames) {}

    bool isPageValid(int virtualPage) {
        return table.find(virtualPage) != table.end() && table[virtualPage].valid;
    }

    void insertPage(int virtualPage, int frameNumber) {
        table[virtualPage] = {frameNumber, true};
        lruQueue.push(virtualPage);
    }

    int evictPage() {
        int evictedPage = lruQueue.front();
        lruQueue.pop();
        table[evictedPage].valid = false;
        return table[evictedPage].frameNumber;
    }
};

class MemoryManagementUnit {
public:
    MMUPageTable *pageTable = new MMUPageTable(8);
    SystemMemory *RAM = new SystemMemory();

    void accessPage(int virtualPage) {
        if (!pageTable->isPageValid(virtualPage)) {
            handlePageFault(virtualPage);
            tlbMisses++;
            pageFaults++;
        }
        else
        {
            cout << "\t\tAccessed Virtual Page: " << virtualPage << endl;
            tlbHits++;
        }
    }

    void handlePageFault(int virtualPage) {
        cout << "Page Fault: Virtual Page " << virtualPage << endl;

        if (pageTable->lruQueue.size() >= pageTable->totalFrames) {
            int evictedFrame = pageTable->evictPage();
            RAM->freeFrame(evictedFrame);
        }

        int newFrame = RAM->allocateFrame();
        pageTable->insertPage(virtualPage, newFrame);
    }
};

#endif