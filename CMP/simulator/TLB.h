#ifndef TLB_H
#define TLB_H

class TLB
{
    int entries;
    int numId;
    int pageSize;
    int pageOffset;
    int vpn[100], ppn[100], valid[100];
    int lastUsed[100];
    static int timeStamp;

public:
    TLB(int ,int);
    TLB();

    bool getPa(int, int&);
    void update(int,int);

    void print();
};

#endif
