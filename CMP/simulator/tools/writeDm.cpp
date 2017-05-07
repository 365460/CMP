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
    FILE *fp = fopen("../dimage.bin", "wb");

    int num = 3;
    writeWord2File(12, fp);
    writeWord2File(num, fp);

    //01010101 01010101 01010101 01010101
    writeWord2File(1431655765, fp);
    //10101010 10101010 10101010 10101010
    writeWord2File(2863311530, fp);
    //10101010 10101010 10101010 10101010
    writeWord2File(2863311530, fp);
    //10101010 10101010 10101010 10101010
    writeWord2File(2863311530, fp);

    fclose(fp);
}
// 1024 bytes
// 1024/4 = 256
