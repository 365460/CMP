#ifndef DATASYSTEM_H
#define DATASYSTEM_H
#include "Memory.h"
#include "Cache.h"
#include "TLB.h"
#include "PGT.h"

class DS{
    int disk[300];
    Memory mem;
    Cache cache;
    TLB tlb;
    PGT pgt;

public:
    DS();
    DS(int data[]);

    int loadData(int);
    int saveData(int,int);
};

#endif
