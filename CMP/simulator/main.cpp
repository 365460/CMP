#include <iostream>
#include <map>
#include <cstdio>
using namespace std;

#include "CPU.h"

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
        cpu->initData("iimage.bin", "dimage.bin");
    }
    catch(Error e)
    {
        cout << e.illegal << endl;
        return 0;
    }

    cpu->printReport(0);

    int cycle = 1;
    for(cycle=1; cycle<=500000; cycle++){
        cpu->runCycle(cycle);
        if(cpu->halt) break;
        // Instruction *nowInst = NULL;
        // int nowAddress = cpu->PC;
        // try
        // {
        //     nowInst = im->fetch(nowAddress);
        // }
        // catch(Error e){
        //     cout << e.illegal << endl;
        //     halt = true;
        //     break;
        // }
        //
        // cpu->PC += 4;
        // cpu->err.message.clear();
        // try{
        //     nowInst->run( cpu );
        //     if(cpu->err.message.size() == 0 && cpu->err.halt==false)
        //         cpu->printReport(cycle);
        //     else
        //     {
        //         if(cpu->err.message.size()==0) // jush halt
        //             halt = true;
        //         else{
        //             for(auto i: cpu->err.message)
        //                 fprintf(ferror, "In cycle %d: %s\n",cycle, i.c_str());
        //         }
        //
        //         if(cpu->err.halt == true) halt = true;
        //         else cpu->printReport(cycle);
        //     }
        // }
        // catch(Error e){
        //     printf("illegal instruction found at 0x%X\n", nowAddress);
        //     halt = true;
        // }
    }
    // fclose( fresult );
    // fclose( ferror );
    // if(!halt) printf("illegal cycles, over 500,000 cycles\n");

    // int n;
    // while(cin>>n){}
    return 0;
}
