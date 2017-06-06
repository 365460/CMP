#include "TLB.h"
#include <cmath>
#include <iostream>
using namespace std;

TLB::TLB(){}
extern int bb;
TLB::TLB(int entries,int pageSize){
    this->entries = entries;
    this->pageSize = pageSize;
    this->pageOffset = log2(pageSize);
    numId = 0;

    for(int i=0; i<=entries; i++){
        valid[i] = false;
        ppn[i] = vpn[i] = 0;
        lastUsed[i] = -1;
    }
}

bool TLB::getPa(int vaddr,int& paddr, int cycle){
    int pageNumber = vaddr >> pageOffset;
    int offset = vaddr - (pageNumber<<pageOffset);

    if(bb) cout << "tlb get "<< vaddr << " " << pageNumber << endl;
    bool find = false;
    for(int i=0; i<entries; i++){
        if(valid[i] && vpn[i]==pageNumber){
            paddr =  (ppn[i]<<pageOffset) + offset;
            lastUsed[i] = cycle;
            find = true;
            break;
        }
    }
    return find;
}

void TLB::update(int vaddr, int paddr, int cycle){
    int target ;
    int vn = vaddr >> pageOffset;
    int pn = paddr >> pageOffset;


    /* notic */
    for(int i=0; i<entries; i++) if(valid[i] &&  ppn[i]==pn)
        valid[i] = false;

    bool find = false;
    for(int i=0; i<entries && !find; i++) if(valid[i]==false){
        target = i;
        find = true;
    }

    /* full */
    if(find==false){
        target = 0;
        for(int i=1; i<entries; i++) if(lastUsed[i] < lastUsed[ target ]){
            target = i;
        }
    }


    ppn[ target ] = pn;
    vpn[ target ] = vn;
    valid[ target ] = true;
    lastUsed[ target ] = cycle;
}

void TLB::print(){
    cout << "tlb entires = " << entries <<endl;
    cout << "pagesize = " << pageSize << endl;
    cout << "num  = " << numId << endl;
    for(int i=0; i<entries; i++){
        printf("%2d%4d%4d%5d\n",valid[i], vpn[i], ppn[i], lastUsed[i]);
    }
    cout << endl;
}
