#include "TLB.h"

TLB::TLB(){}

TLB::TLB(int entries,int pageSize){
    this->entries = entries;
    this->pageSize = pageSize;
    num = 0;

    for(int i=0; i<100; i++){
        valid[i] = false;
        pa[i] = va[i] = 0;
    }
}
