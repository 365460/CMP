#ifndef CPU_H
#define CPU_H

#include <cstring>
#include <cstdio>
#include <vector>
#include "Error.h"
#include "DataSystem.h"
using std::string;

class CPU
{
    void loadMem(string,int[]);
    void loadInst(string,int[]);
public:

    int memory[233];
    /* Data System*/
    int size[2], pageSize[2], cacheSize[2], blockSize[2], nWay[2];
    DS *instDs, *dataDs;

    /* register */
    int reg[35]; // 32: HI, 33: LO
    unsigned int PC;
    bool hadgethi;

    /*  snapshot.rpt */
    FILE *fresult;
    FILE *ferror;
    FILE *freport;
    std::vector<int> report;
    Error err;
    bool halt;

    CPU(int arg[]);
    ~CPU();
    void initData(string,string);
    void setReg(int address,int code);
    int fetch();

    void printSnap(int cycle);
    void printError(int cycle);
    void printReport();
    void printPC();
};
#endif
