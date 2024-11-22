#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int PAGE_SIZE = 0x1000;//4KB = 12 bits offset
const int NUM_VIRTUAL_PAGES = 16;//# of virtual pages
const int NUM_PHYS_PAGES = 8;//# of physical pages
const int TLB_SIZE = 4;//TLB size limit

vector<int> tlbEntries;//virtual pages in the TLB (FIFO Queue)

//external variables
extern int tlbHits;
extern int tlbMisses;
extern int pageFaults;

class PageTableEntry {
public:
    int physicalPage; //physical page number
    bool valid;//valid for 1 or 0
};

PageTableEntry pageTable[NUM_VIRTUAL_PAGES];//page table for all virtual pages

//current page table
void printPageTable() {
    cout << "Page Table:\n";
    cout << "Virtual Page\tPhysical Page\tValid\n";
    for (int i = 0; i < NUM_VIRTUAL_PAGES; i++) {
        cout << i << "\t\t" << pageTable[i].physicalPage << "\t\t" << pageTable[i].valid << "\n";
    }
    cout << endl;
}

//page table with unique physical page
void initializePageTable() {
    srand(static_cast<unsigned>(time(0)));
    vector<bool> physicalPagesAssigned(NUM_PHYS_PAGES, false);
    for (int i = 0; i < NUM_VIRTUAL_PAGES; i++) {
        int physicalPage;
        int attempts = 0;
        do {
            physicalPage = 100 + (rand() % 900);
            attempts++;
            if (attempts > NUM_PHYS_PAGES) {
                break;
            }
        } while (physicalPagesAssigned[physicalPage]);

        physicalPagesAssigned[physicalPage] = true; //mark page as assigned
        pageTable[i].physicalPage = physicalPage;
        pageTable[i].valid = rand() % 2;//random valid/invalid
    }
    cout << "[Page Table Initialized with Unique Physical Page]\n";
    printPageTable();
}


//TLB using FIFO
void updateTLB(int virtualPage) {
    //check if the virtual page is already in the TLB
    if (find(tlbEntries.begin(), tlbEntries.end(), virtualPage) == tlbEntries.end()) {
        //if TLB is full remove the first
        if (tlbEntries.size() >= TLB_SIZE) {
            int removedPage = tlbEntries.front();
            tlbEntries.erase(tlbEntries.begin());
            cout << "[TLB Eviction] Removed Virtual Page " << removedPage << endl;
        }
        //add new virtual page
        tlbEntries.push_back(virtualPage);
        cout << "[TLB Updated] Virtual Page " << virtualPage << " added to TLB." << endl;
    }
}

//check if a virtual page is in the TLB
bool checkTLB(int virtualPage) {
    for (size_t i = 0; i < tlbEntries.size(); ++i) {
        if (tlbEntries[i] == virtualPage) {
            cout << "TLB Hit: Virtual Page " << virtualPage << " is in TLB at index " << i << "." << endl;
            return true;
        }
    }
    cout << "TLB Miss: Virtual Page " << virtualPage << " not found in TLB." << endl;
    return false;
}

//page fault
void handlePageFault(int virtualPage) {
    if (!pageTable[virtualPage].valid) {
        pageFaults++;
        pageTable[virtualPage].valid = 1;
        pageTable[virtualPage].physicalPage = rand() % NUM_PHYS_PAGES;
        cout << "[Page Fault Resolved] Virtual Page " << virtualPage
             << " mapped to Physical Page " << pageTable[virtualPage].physicalPage << endl;
    }
}

//translate a virtual address to a physical address
int translateAddress(int virtualAddress) {
    int virtualPage = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;

    cout << "[Performing Address Translation]\n";
    cout << "Virtual Address: 0x" << hex << virtualAddress << "\n";
    cout << "Page: 0x" << hex << virtualPage << ", Offset: 0x" << hex << offset << "\n";

    if (checkTLB(virtualPage)) {
        cout << "[TLB Hit] Virtual Page " << virtualPage << " found in TLB.\n";
        tlbHits++;
        return (pageTable[virtualPage].physicalPage * PAGE_SIZE) + offset;
    } else {
        cout << "[TLB Miss] Virtual Page " << virtualPage << " not in TLB.\n";
        tlbMisses++;
        if (!pageTable[virtualPage].valid) {
            cout << "Page Fault Detected: Virtual Page " << virtualPage << "\n";
            handlePageFault(virtualPage);
        }
        updateTLB(virtualPage);
        return (pageTable[virtualPage].physicalPage * PAGE_SIZE) + offset;
    }
}

//current TLB contents
void printTLB() {
    cout << "Current TLB: ";
    for (size_t i = 0; i < tlbEntries.size(); i++) {
        cout << tlbEntries[i] << " ";
    }
    cout << endl;
}

#endif
