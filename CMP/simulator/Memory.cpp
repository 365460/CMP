#include "Memory.h"
#include <cmath>

int Memory::timeStamp = 0;
Memory::Memory(int size,int pageSize){
    this->size = size;
    this->pageSize = pageSize;
    this->totalPages = size / pageSize;

    this->pageOffset = log2(pageSize);
    numId = 0;
    for(int i=0; i<totalPages; i++) LRU[i] = dirty[i] = 0;
}

int Memory::getdate(int addr){
    int pageid = addr>>pageOffset;
    int dataid = (addr-(pageid<<pageOffset) )>>2;
    LRU[ pageid ] = ++timeStamp;
    return mem[pageid].data[ dataid ];
}

// return pa address
int Memory::update(int addrDisk,int disk[]){
    int tarPageId = 0;
    if(numId==totalPages){
        for(int i=0; i<totalPages; i++){
            if(LRU[i] < LRU[tarPageId]) tarPageId = i;
        }

        if(dirty[tarPageId]){
            int diskbase = pageIdInDisk[tarPageId]*pageSize;

            for(int i=0; i<(pageSize>>2); i++){
                disk[ (diskbase>>2) ] = mem[tarPageId].data[i];
                diskbase += 4;
            }
        }
    }else tarPageId = numId++;

    dirty[ tarPageId ] = 0;
    LRU[ tarPageId ] = ++timeStamp;
    pageIdInDisk[ tarPageId ] = addrDisk>>pageOffset;
    int diskbase = pageIdInDisk[tarPageId]*pageSize;
    for(int i=0; i<(pageSize>>2); i++){
        mem[tarPageId].data[i] = disk[(diskbase>>2)];
        diskbase += 4;

        /* notice */
    }
    return (tarPageId<<pageOffset) + (addrDisk - ((addrDisk>>pageOffset)<<pageOffset));
}

void Memory::print(){
    for(int i=0; i<numId; i++){
        printf("Disk addr = %d\n",pageIdInDisk[i]*pageSize);
        for(int j=0; j<pageSize/4; j++){
            printf("%d:%d\n",i*pageSize+j*4, mem[i].data[j]);
        }
    }
}
