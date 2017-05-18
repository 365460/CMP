#include <iostream>
#include <map>
#include <cstdio>
using namespace std;

#include "CPU.h"
#include "Instruction.h"

int bb = 0;
int to_Int(char *s){
    int ans = 0, l = strlen(s);
    for(int i=0; i<l; i++){
        ans = ans*10 + s[i]-'0';
    }
    return ans;
}
int main(int argc, char* arg[])
{
    int data[12] = {64, 32, 8, 16, 16, 4, 4, 16, 4, 1};
    for(int i=1; i<argc; i++)
        data[i-1] = to_Int(arg[i]);

    CPU* cpu = new CPU(data);

    try
    {
        // cpu->initData("iimage.bin", "dimage.bin");
        cpu->initData("../../archiTA/simulator/iimage.bin", "../../archiTA/simulator/dimage.bin");
    }
    catch(Error e)
    {
        cout << e.illegal << endl;
        return 0;
    }

    cpu->printSnap(0);

    int cycle = 1;
    for(cycle=1; cycle<=500000 && cpu->halt==false; cycle++){
        bb = 0;
        Instruction *inst = decode( cpu->fetch() );

        cpu->PC += 4;
        // printf("-------------------\n");
        // printf("     ");
        bb = 0;
        inst->run(cpu);
        // printf("\n");
        if(cpu->err.halt || cpu->halt) break;

        // printf("%d, ",cycle);
        // inst->print();
        // cpu->instDs->print();
        // cpu->dataDs->print();

        cpu->printSnap(cycle);
        cpu->printError(cycle);
        // cpu->printReport();
        // fprintf(cpu->freport, "------\n\n");
        // printf("\n\n");
    }
    cpu->printReport();
    if(!(cpu->err.halt || cpu->halt)) printf("illegal cycles, over 500,000 cycles\n");

    // int n;
    // while(cin>>n){}
    return 0;
}
