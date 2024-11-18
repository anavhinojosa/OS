#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int PAGE_SIZE = 0x1000;//4KB = 12 bits offset
const int OFFSET_BITS = 12;//# of offset
const int NUM_PAGES = 16;//# of virtual pages
const int NUM_PHYS_PAGES = 8;//# of physical pages

#endif