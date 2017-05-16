#include "TLB.h"
#include <cmath>
#include <iostream>
using namespace std;

int TLB::timeStamp = 0;
TLB::TLB(){}

TLB::TLB(int entries,int pageSize){
    this->entries = entries;
    this->pageSize = pageSize;
    this->pageOffset = log2(pageSize);
    numId = 0;

    for(int i=0; i<100; i++){
        valid[i] = false;
        ppn[i] = vpn[i] = 0;
        lastUsed[i] = 0;
    }
}

bool TLB::getPa(int vaddr,int& paddr){
    int pageNumber = vaddr >> pageOffset;
    int offset = vaddr - (pageNumber<<pageOffset);

    int debug = false;
    if(debug) printf("tlb get vaddr = %d, pn=%d, off=%d\n",vaddr,pageNumber, offset);
    bool find = false;
    for(int i=0; i<numId; i++){
        if(valid[i] && vpn[i]==pageNumber){
            paddr =  (ppn[i]<<pageOffset) + offset;
            lastUsed[i] = ++TLB::timeStamp;
            if(debug) printf("find %d\n",paddr);
            find = true;
        }
    }
    return find;
}

void TLB::update(int vaddr, int paddr){
    int target ;
    int vn = vaddr >> pageOffset;
    int pn = paddr >> pageOffset;
    if(numId == entries){ // replacement
        target = 0;
        for(int i=0; i<numId; i++) if( lastUsed[i] < lastUsed[ target ])
            target = i;

    }else target = numId++;

    /* notic */
    for(int i=0; i<numId; i++) if(valid[i] &&  ppn[i]==pn)
        valid[i] = false;

    ppn[ target ] = pn;
    vpn[ target ] = vn;
    valid[ target ] = true;
    lastUsed[ target ] = ++TLB::timeStamp;
}

void TLB::print(){
    cout << "num  = " << numId << endl;
    for(int i=0; i<numId; i++){
        printf("%2d%4d%4d\n",valid[i], vpn[i], ppn[i]);
    }
    cout << endl;
}
