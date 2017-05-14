#include "PGT.h"

PGT::PGT(){}

PGT::PGT(int pageSize)
{
    this->DiskSize = 1024;
    this->pageSize = pageSize;
    this->entries = DiskSize/pageSize;

    for(int i=0; i<300; i++){
        valid[i] = false;
        pa[i] = va[i] = 0;
    }
}
