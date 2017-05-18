#include "DataSystem.h"

extern int bb;
DS::DS(){}

DS::DS(int data[],int memSize, int pageSize,int cacheSize, int blockSize
    ,int nWay)
{
    mem = new Memory(memSize, pageSize);
    cache = new Cache(cacheSize, blockSize, nWay);
    pgt = new PGT(pageSize);
    tlb = new TLB((1024/pageSize)/4, pageSize);
    cachehit = cachemiss = 0;
    tlbhit = tlbmiss = 0;
    pgthit = pgtmiss = 0;

    for(int i=0; i<1024/4; i++){
        disk[i] = data[i];
    }

}

int DS::loadData(int vaddr){
    int paddr, data;

    int debug = false;
    int debugL = bb;
    // if(debugL) printf("ask %d\n",vaddr);
    if(tlb->getPa(vaddr, paddr)==true){
        if(debugL) printf("ITLB ");
        if(debug) printf(" tlb ");
        tlbhit++;
        if(debug) printf("from tlb paddr = %d\n", paddr);
        if(cache->getdata(paddr, data)==true){
            // if(debugL) printf("H X\n");
            if(debug) printf(" cache ");
            cachehit++;
            return data;
        }
        else{ // cache miss
            // if(debugL) printf("M X\n");
            if(debug) printf("cache miss\n" );
            if(debug) printf(" memory ");
            cachemiss++;
            cache->update(paddr, mem);
            cache->getdata(paddr, data);
            return data;
        }
    }
    else{ // tlb miss
        tlbmiss++;
        if(debugL) printf("DISK ");
        if(pgt->getPa(vaddr, paddr)==true){
            pgthit++;
            tlb->update(vaddr, paddr);
            if(cache->getdata(paddr, data)==true){
                // if(debugL) printf("H H\n");
                cachehit++;
                return data;
            }
            else{
                // updata cache
                // if(debugL) printf("M H\n");
                cachemiss++;
                cache->update(paddr, mem);
                cache->getdata(paddr, data);
                return data;
            }
        }
        else{ // page fault
            // if(debugL) printf("DISK ");
            if(debug) printf("page fault\n");
            pgtmiss++;
            cachemiss++;
            int paddr = mem->update(vaddr, disk);
            int paddrbase = (paddr>>mem->pageOffset)<<mem->pageOffset;
            for(int i=0; i<(mem->pageSize>>2); i++){
                cache->setValid( paddrbase + i*4, false);
            }

            if(debug) printf("pgt update %d %d\n",vaddr, paddr);
            pgt->update(vaddr,paddr);

            if(debug) printf("tlb update\n");
            tlb->update(vaddr, paddr);

            if(debug) printf("cache update\n");
            cache->update(paddr, mem);

            if(debug) printf("cache get data\n");
            cache->getdata(paddr, data);
            if(debug) printf("data = %d\n", data);
            return data;
        }

    }
    return 0;
}

void DS::saveData(int vaddr,int val){
    int paddr;
    tlb->getPa(vaddr, paddr);
    cache->savedata(paddr, val);
    mem->savedate(paddr, val);
}

void DS::print(){
    printf("memory : \n");
    mem->print();

    printf("cache : \n");
    cache->print();

    printf("Tlb : \n");
    tlb->print();

    pgt->print();
}
