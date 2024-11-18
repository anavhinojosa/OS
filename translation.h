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
  for (int i = 0; i < NUM_VIRTUAL_PAGES; i++){
    pageTable[i].physicalPage = rand() % NUM_PHYS_PAGES;
    pageTable[i].valid = rand() % 2;
  }
}

void translateAddress(int virtualAddress){
  //this would translate the virtual address to a physical address
}

void printPageTable(){
  cout << "Page Table" << endl;
  cout << "Virtual Page | Physical Page | Valid" << endl;
  for (int i = 0; i < NUM_VIRTUAL_PAGES; i++){
    cout << " " << i << " " << pageTable[i].physicalPage
    << " " << pageTable[i].valid << endl;
  }
}

#endif