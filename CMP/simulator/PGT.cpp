#include "PGT.h"
#include <cstdio>
#include <cmath>

PGT::PGT(){}

PGT::PGT(int pageSize)
{
    this->DiskSize = 1024;
    this->pageSize = pageSize;
    this->pageOffset = log2(pageSize);

    this->entries = DiskSize/pageSize;
    numId = 0;

    for(int i=0; i<300; i++){
        valid[i] = false;
        ppn[i] = vpn[i] = 0;
    }
}

bool PGT::getPa(int vaddr,int& paddr){
    bool find = false;
    int poff = vaddr - ((vaddr>>pageOffset)<<pageOffset);
    for(int i=0; i<numId; i++){
        if(valid[i] && vpn[i]==(vaddr>>pageOffset)){
            find = true;
            paddr = (ppn[i]<<pageOffset) + poff;
        }
    }
    return find;
}

void PGT::update(int vaddr,int paddr){
    for(int i=0; i<numId; i++){
        if(valid[i] && ppn[i]==(paddr>>pageOffset) ){
            valid[i] = 0;
        }
    }
    int tar = numId;
    for(int i=0; i<numId; i++){
        if(vpn[i]==(vaddr>>pageOffset)){
            tar = i;
            break;
        }
    }
    valid[tar] = 1;
    vpn[tar] = vaddr>>pageOffset;
    ppn[tar] = paddr>>pageOffset;

    if(tar == numId) numId += 1;
}

void PGT::print(){
    printf("PGT: \n");
    for(int i=0; i<numId; i++){
        printf("%d %d %d\n", valid[i], vpn[i], ppn[i]);
    }
    printf("\n");
}
