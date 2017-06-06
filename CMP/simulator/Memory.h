#ifndef IMEMORY_H
#define IMEMORY_H

#include <cstdio>

struct Page{
    int data[256]; // one page has maximum 256 words
};

class Memory{

    Page mem[300];
    int dirty[300]; // if page is dirty
    int LRU[300];
    int pageIdInDisk[300];

    int timeStamp;
public:
    int size, pageSize; // bytes
    int pageOffset; // log2(pageSize)
    int totalPages; // size/pageSize
    int numId; // pageCounter == totalPages --> find vict
    Memory(int,int);

    int getdate(int addr);
    void updateLRU(int addr,int cycle);
    void savedate(int ,int);
    int update(int addr,int[]);
    void print();
};
/*
pageCounter
            0|      |
    0       4| page |
            8|      |
           12|______|
           16|      |
    1      20|      |
             |      |
             |______|
             |      |
             |      |
    2        |      |
             |      |
*/

#endif
