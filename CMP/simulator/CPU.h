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
    DS *instDs, *dataDs;

    /* register */
    int reg[35]; // 32: HI, 33: LO
    unsigned int PC;
    bool hadgethi;

    /*  snapshot.rpt */
    FILE *fresult;
    FILE *ferror;
    std::vector<int> report;
    Error err;
    bool halt;

    CPU(int arg[]);
    ~CPU();
    void initData(string,string);
    void runCycle(int);
    void setReg(int address,int code);
    void printReport(int cycle);
    void printPC();
};
#endif
