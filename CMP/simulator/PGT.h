#ifndef PAGETABLE_H
#define PAGETABLE_H

class PGT
{
    int pageSize;
    int pageOffset;
    int DiskSize;
    int entries;
    int numId;
    int ppn[300], vpn[300], valid[300];

public:
    PGT(int);
    PGT();
    bool getPa(int,int &);
    void update(int,int);

    void print();
};
#endif
