#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int PAGE_SIZE = 0x1000;//4KB = 12 bits offset
const int OFFSET_BITS = 12;//# of offset
const int NUM_VIRTUAL_PAGES = 16;//# of virtual pages
const int NUM_PHYS_PAGES = 8;//# of physical pages

class PageTableEntry{
  public:
    int physicalPage;//phsyical page number
    bool valid;//1 is valid, 0 is invalid
};

//page table
PageTableEntry pageTable[NUM_VIRTUAL_PAGES];

void initializePageTable(){
  srand(static_cast<unsigned>(time(0)));//seed
  for (int i = 0; i < NUM_VIRTUAL_PAGES; i++){
    pageTable[i].physicalPage = rand() % NUM_PHYS_PAGES;//random physical address
    pageTable[i].valid = rand() % 2;//random valid/invalid
  }
}

int translateAddress(int virtualAddress){
  //this would translate the virtual address to a physical address
  int virtualPage = virtualAddress / PAGE_SIZE;//virtual page = address / page size
  int offset = virtualAddress % PAGE_SIZE;//offset = address % page size
  cout << "Translating Virtual Address: 0x" << hex << virtualAddress << endl;
  cout << "Virtual Page: " << virtualPage << ", Offset: 0x" << hex << offset << endl;

  //check if the virtual page is valid
  if(pageTable[virtualPage].valid) {
    //if valid compute the physical address
    int physicalPage = pageTable[virtualPage].physicalPage;
    int physicalAddress = (physicalPage * PAGE_SIZE) + offset;//combine physical page and offse
    //output physical address
    cout << "Physical Address: 0x" << hex << physicalAddress << endl;
    return physicalAddress;
  }
  else {
    //if invalid:
    cout << "Page Fault. Virtual Page " << virtualPage << " is invalid." << endl;
    return -1;//page fault
  }
}

void printPageTable() {
  cout << "Page Table:" << endl;
  cout << "Virtual Page | Physical Page | Valid" << endl;
  for (int i = 0; i < NUM_VIRTUAL_PAGES; i++) {
    cout << "  " << i << "   " << pageTable[i].physicalPage
         << "    " << pageTable[i].valid << endl;
  }
}

#endif