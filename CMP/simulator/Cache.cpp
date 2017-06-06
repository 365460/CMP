#include "Cache.h"
#include <cmath>

extern int bb;
static int getCode(int code,int a,int b){  // get a to b
    int res = 0;
    for(int i=a, j = 0; i<=b; i++,j++) if((code>>i)&1){
        res += (1<<j);
    }
    return res;
}
void Set::init(){
    valid = false;
    tag = 0;
}

void Set::setValid(bool v){
    valid = v;
}

void Set::setData(int tag, int* d,int numWord){
    for(int i=0; i<numWord; i++) data[i] = d[i];
    valid = true;
    this->tag = tag;
}

Cache::Cache(){}

Cache::Cache(int totalSize, int blockSize, int nWay){
    this->totaleSize = totalSize;
    this->blockSize = blockSize;
    this->blockOffset = log2(blockSize);
    this->nWay = nWay;

    this->entries = totalSize/(blockSize*nWay);
    this->entriesOffset = log2(entries);
    this->blockDeep = blockSize/4;

    for(int i=0; i<=entries; i++)
        for(int j=0; j<300; j++){
            set[i][j].init();
            MRU[i][j] = 0;
        }

    for(int i=0; i<=entries; i++) MruOneNum[i] = 0;
}

int Cache::getId(int addr){
    return getCode(addr, blockOffset, blockOffset+entriesOffset-1);
}

int Cache::getTag(int addr){
    return getCode(addr, blockOffset+entriesOffset, 31);
}

void Cache::setValid(int addr, bool val){
    int id = getId(addr);
    int tag = getTag(addr);

    for(int i=0; i<nWay; i++){
        if(set[id][i].valid && set[id][i].tag == tag)
            set[id][i].valid = val;
    }

}

bool Cache::getdata(int addr, int& val){
    int id = getId(addr);
    int tag = getTag(addr);
    int blockdeep = (unsigned)addr<<(32-blockOffset)>>(32-blockOffset);
    blockdeep>>=2; // cut bytesoffset;

    bool find = false;
    for(int i=0; i<nWay; i++){
        if(set[id][i].valid && set[id][i].tag == tag){
            find = true;
            val = set[id][i].data[ blockdeep ];

            if(MRU[id][i]==0) MruOneNum[id]++;
            MRU[id][i] = 1;
            if(MruOneNum[id]>=nWay) cleanMru(id, i);
        }
    }
    return find;
}

void Cache::savedata(int addr, int val){
    int id = getId(addr);
    int tag = getTag(addr);
    int blockdeep = (unsigned)addr<<(32-blockOffset)>>(32-blockOffset);
    blockdeep>>=2; // cut bytesoffset;

    for(int i=0; i<nWay; i++){
        if(set[id][i].valid && set[id][i].tag==tag){
            set[id][i].data[blockdeep] = val;
        }
    }
}

void Cache::update(int addr, Memory *mem, int cycle){
    int id = getId(addr);
    int tag = getTag(addr);
    int base = (tag<<(blockOffset+entriesOffset))+(id<<blockOffset);

    int data[blockDeep];
    for(int i=0; i<(blockSize>>2); i++){
        data[i] = mem->getdate(base);
        base += 4;
    }

    int tar = 0;
    bool find = false;

    for(int i=0; i<nWay && !find; i++) if(set[id][i].valid == false){
        tar = i;
        find = true;
    }
    for(int i=0; find==false && i<nWay; i++){
        if(MRU[id][i]==0){
            tar = i;
            find = true;
        }
    }
    set[id][ tar ].setData(tag, data, blockDeep);
    //
    // if(MRU[id][tar]==0) MruOneNum[id] ++;
    // MRU[id][tar] = 1;
    // if(MruOneNum[id]>=nWay)
    //     cleanMru(id, tar);
}

void Cache::cleanMru(int id,int tar){
    for(int i=0; i<nWay; i++) MRU[id][i] = 0;
    if(nWay==1) MruOneNum[id] = 0;
    else{
        MRU[id][tar] = 1;
        MruOneNum[id] = 1;
    }

}

void Cache::print(){
    printf("cache %d way\n", nWay);
    for(int i=0; i<entries; i++){
        printf("id = %d: ",i);
        for(int j=0; j<nWay; j++){
            printf("| %2d, %2d, %4d, %4d | ",MRU[i][j], set[i][j].valid, set[i][j].tag, set[i][j].data[0]);
        }
        printf("\n");
    }
}
