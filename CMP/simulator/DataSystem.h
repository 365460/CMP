#ifndef DATASYSTEM_H
#define DATASYSTEM_H
#include "Memory.h"
#include "Cache.h"
#include "TLB.h"
#include "PGT.h"

class DS{
    int disk[300];
    Memory* mem;
    Cache* cache;
    TLB* tlb;
    PGT* pgt;


public:
    int cachehit;
    int cachemiss;

    int tlbhit;
    int tlbmiss;

    int pgthit;
    int pgtmiss;

    DS();
    DS(int[],int,int,int,int,int);

    int loadData(int,int);
    void saveData(int,int,int);
    void print();
};

#endif
