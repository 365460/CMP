#include "Memory.h"
#include <cmath>

Memory::Memory(int size,int pageSize){
    this->size = size;
    this->pageSize = pageSize;
    this->totalPages = size / pageSize;

    this->pageOffset = log2(pageSize);
    numId = 0;
    for(int i=0; i<totalPages; i++) LRU[i] = dirty[i] = 0;
}

void Memory::updateLRU(int addr, int cycle){
    int pageid = addr>>pageOffset;
    LRU[ pageid ] = cycle;
}

int Memory::getdate(int addr){
    int pageid = addr>>pageOffset;
    int dataid = (addr-(pageid<<pageOffset) )>>2;
    return mem[pageid].data[ dataid ];
}

void Memory::savedate(int addr, int val){
    int pageid = addr>>pageOffset;
    int dataid = (addr-(pageid<<pageOffset) )>>2;
    dirty[ pageid ] = true;
    mem[pageid].data[ dataid ] = val;
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
    pageIdInDisk[ tarPageId ] = addrDisk>>pageOffset;
    int diskbase = pageIdInDisk[tarPageId]*pageSize;
    for(int i=0; i<(pageSize>>2); i++){
        mem[tarPageId].data[i] = disk[(diskbase>>2)];
        diskbase += 4;
    }
    return (tarPageId<<pageOffset) + (addrDisk - ((addrDisk>>pageOffset)<<pageOffset));
}

void Memory::print(){
    for(int i=0; i<numId; i++){
        printf("==>         %d: Disk addr = %d, LRU = %d\n",i,pageIdInDisk[i], LRU[i]);
        for(int j=0; j<pageSize/4; j++){
            // printf("%d: 0x%8X\n",i*pageSize+j*4, mem[i].data[j]);
            // printf("%d: %d\n",i*pageSize+j*4, mem[i].data[j]);
        }
    }
}
