#ifndef TLB_H
#define TLB_H

class TLB
{
    int entries;
    int num;
    int pageSize;
    int va[100], pa[100], valid[100];

public:
    TLB(int ,int);
    TLB();

};

#endif
