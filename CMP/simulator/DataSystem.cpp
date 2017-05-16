#include "DataSystem.h"

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
    int location;
    // printf("ask %d\n",vaddr);


    int debug = false;
    if(tlb->getPa(vaddr, paddr)==true){
        printf("H ");
        if(debug) printf(" tlb ");
        tlbhit++;
        if(debug) printf("from tlb paddr = %d\n", paddr);
        if(cache->getdata(paddr, data)==true){
            printf("H X\n");
            if(debug) printf(" cache ");
            cachehit++;
            return data;
        }
        else{ // cache miss
            printf("M X\n");
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
        printf("M ");
        if(pgt->getPa(vaddr, paddr)==true){
            pgthit++;
            tlb->update(vaddr, paddr);
            if(cache->getdata(paddr, data)==true){
                printf("H H\n");
                cachehit++;
                return data;
            }
            else{
                // updata cache
                printf("M H\n");
                cachemiss++;
                cache->update(paddr, mem);
                cache->getdata(paddr, data);
                return data;
            }
        }
        else{ // page fault
            printf("M M\n");
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

int DS::saveData(int vaddr,int val){
    return 0;
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
