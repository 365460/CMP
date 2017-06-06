#include "DataSystem.h"

DS::DS(){}

DS::DS(int data[],int memSize, int pageSize,int cacheSize, int blockSize
    ,int nWay)
{
    mem   = new Memory(memSize, pageSize);
    cache = new Cache(cacheSize, blockSize, nWay);
    pgt   = new PGT(pageSize);
    tlb   = new TLB((1024/pageSize)/4, pageSize);
    cachehit = cachemiss = 0;
    tlbhit = tlbmiss = 0;
    pgthit = pgtmiss = 0;

    for(int i=0; i<1024/4; i++){
        disk[i] = data[i];
    }

}

int DS::loadData(int vaddr,int cycle){
    int paddr, data;

    vaddr = (vaddr>>2) << 2;
    if(tlb->getPa(vaddr, paddr, cycle)==true){ // update tlb LRU
        tlbhit++;
        if(cache->getdata(paddr, data)==true){ // update cache MRU
            cachehit++;
            return data;
        }
        else{ // cache miss
            cachemiss++;
            cache->update(paddr, mem, cycle); // update cache MRU
            cache->getdata(paddr, data);
            return data;
        }
    }
    else{ // tlb miss
        tlbmiss++;
        if(pgt->getPa(vaddr, paddr)==true){
            pgthit++;
            tlb->update(vaddr, paddr, cycle); // update tlb lru
            mem->updateLRU(paddr, cycle);  // update mem LRU because cache hit/miss
            if(cache->getdata(paddr, data)==true){ // update cache MRU
                cachehit++;
                return data;
            }
            else{
                cachemiss++;
                cache->update(paddr, mem, cycle);
                cache->getdata(paddr, data);
                return data;
            }
        }
        else{ // page fault
            pgtmiss++;
            cachemiss++;
            int paddr = mem->update(vaddr, disk); // return pagenumber
            mem->updateLRU(paddr, cycle);

            pgt->update(vaddr,paddr);
            // notic : have to setInvalid before get target id
            tlb->update(vaddr, paddr, cycle);

            int paddrbase = (paddr>>mem->pageOffset)<<mem->pageOffset;
            for(int i=0; i<(mem->pageSize>>2); i++){
                cache->setValid( paddrbase + i*4, false);
            }
            cache->update(paddr, mem, cycle);
            cache->getdata(paddr, data);
            return data;
        }
    }
    return 0;
}

// any instruction needing writing back has to call loadData first
void DS::saveData(int vaddr,int val,int cycle){
    vaddr = (vaddr>>2 ) << 2;
    int paddr;
    tlb->getPa(vaddr, paddr, cycle);
    cache->savedata(paddr, val);
    mem->savedate(paddr, val); // write through
}

void DS::print(){
    printf("memory : \n");
    // mem->print();

    // printf("cache : \n");
    // cache->print();
    //
    printf("Tlb : \n");
    tlb->print();

    pgt->print();
}
