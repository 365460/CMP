#include <iostream>
#include <cstdio>
using namespace std;
void writeWord2File(unsigned int x, FILE *fp){
    int id = 7;
    unsigned char c = 0;
    for(int i=31; i>=0; i--){
        if((x>>i)&1) c |= 1<<id;
        id -= 1;

        if(id==-1){
            fwrite(&c, sizeof(unsigned char), 1, fp);
            id = 7;
            c = 0;
        }
    }
}
int main()
{
    FILE *fp = fopen("../../../archiTA/simulator/dimage.bin", "wb");

    int num = 16;
    writeWord2File(12, fp);
    writeWord2File(num, fp);

    for(int i=0; i<=60; i+=4)
    writeWord2File(i, fp); //0
    // writeWord2File(16, fp);//4
    // writeWord2File(20, fp);//8
    //01010101 01010101 01010101 01010101
    // writeWord2File(-4, fp);//12
    //10101010 10101010 10101010 10101010
    // writeWord2File(-5, fp);//16
    //10101010 10101010 10101010 10101010
    // writeWord2File(2863311530, fp);
    //10101010 10101010 10101010 10101010
    // writeWord2File(2863311530, fp);

    fclose(fp);
}
// 1024 bytes
// 1024/4 = 256
