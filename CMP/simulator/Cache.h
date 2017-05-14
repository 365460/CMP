#ifndef CACHE_H
#define CACHE_H

class Cache{
    int totaleSize;
    int nWay;
    int blockSize;
    int entries;

    int data[260][260]; // index, tag ...
    int valid[260][260];

public:

    Cache();
    Cache(int ,int ,int);
    int replace();
    int writeback();
    int getdata();
};


#endif
