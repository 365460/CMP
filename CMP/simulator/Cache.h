#ifndef CACHE_H
#define CACHE_H

#include "Memory.h"

struct Set{
    bool valid;
    int tag;
    // --> pa == tag_id << blockOffset
    int data[300]; // word*deep

    void init();
    void setValid(bool);
    void setData(int,int[],int);
};

class Cache{
    int totaleSize;
    int nWay;
    int blockSize;
    int blockOffset;

    int blockDeep; // blockSize/4;
    int entries;    // size/(nWay*blockSize)
    int entriesOffset;

    Set set[300][300];
    // int num[300];

    int MRU[300][300];
    int MruOneNum[300];

    int getId(int);
    int getTag(int);
    void cleanMru(int,int);

public:

    Cache();
    Cache(int ,int ,int);
    bool getdata(int,int&);
    void savedata(int,int);
    void update(int,Memory *mem,int cycle);
    void print();
    void setValid(int , bool);
};

/*

id             set0(block)                          set1(block)
0   |_v_|_tag_|__blocksize = word*n__| |_v_|_tag_|__blocksize = word*n__| .....
1   |_v_|_tag_|__blocksize = word*n__| |_v_|_tag_|__blocksize = word*n__| .....
.
.
.

*/
#endif
