#ifndef PAGETABLE_H
#define PAGETABLE_H

class PGT
{
    int pageSize;
    int DiskSize;
    int entries;
    int pa[300], va[300], valid[300];

public:
    PGT(int);
    PGT();
    int get(int address);
};
#endif
