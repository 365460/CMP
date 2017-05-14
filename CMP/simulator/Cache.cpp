#include "Cache.h"

Cache::Cache(){}

Cache::Cache(int totalSize, int blockSize, int nWay){
    this->totaleSize = totalSize;
    this->blockSize = blockSize;
    this->nWay = nWay;

    this->entries = totalSize/(blockSize*nWay);
}
