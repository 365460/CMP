#include "CPU.h"

CPU::CPU(int arg[]){

    ferror =  fopen("error_dump.rpt", "w");
    fresult = fopen("snapshot.rpt", "w");

    hadgethi = true;
    halt = false;

    for(int i=0; i<34; i++){
        report.push_back(i);
        reg[i] = 0;
    }
}

CPU::~CPU(){
    fclose(ferror);
    fclose(fresult);
}

void CPU::initData(string memFile, string instFile){
    int memory[300], inst[300];
    for(int i=0; i<300; i++) memory[i] = 0;
    for(int i=0; i<300; i++) inst[i] = 0;

    loadMem(memFile, memory);
    loadInst(instFile, inst); // init pc

    this->instDs = new DS(inst);
    this->dataDs = new DS(memory);
}

void CPU::loadMem(string filename, int memory[]){
    FILE *fp = fopen(filename.c_str(),"rb");
    if(fp==NULL) throw Error("no dimage.bin");
    char s[4];
    int T = 0, num = 0;
    int id = 0;
    while(fscanf(fp,"%c",&s[0])==1){
        for(int i=1; i<4; i++) fscanf(fp,"%c",&s[i]);
        int code = 0, base = 24;
        for(int j=0; j<4; j++, base -= 8){
            int t2 = (unsigned)s[j]<<24>>24;
            code |= (t2<<base);
        }
        if(T==0) reg[ 29 ] = code; // init $sp
        else if(T==1){
            num = code;
        }
        else{
            if( id>=256)
                throw Error("dllegal Dimage..., loaded address is over 1K");
            memory[ id++ ] = code;
            if(id==num) break;
            // printf("mem : %d = 0x%08X\n",code, code);
        }
        T++;
    }

    if(id!=num) // num of input data != num
        throw Error("illegal Dimage..., loaded words isn't a complete word");

    fclose(fp);
}
// num is over 256 and num of input isn't equql num
// ==> loaded words isn't a complete word


void CPU::loadInst(string filename, int inst[]){
    FILE *fp = fopen(filename.c_str(), "rb");
    if(fp==NULL) throw Error("no iimage.bin");

    char s[4];
    int T = 0, nowaddress = 0, start, end;
    while(fscanf(fp,"%c",&s[0])==1){
        for(int i=1; i<4; i++) fscanf(fp,"%c",&s[i]);
        int code = 0;
        int base = 24;
        for(int j=0; j<4; j++, base -= 8){
            int t2 = (unsigned)s[j]<<24>>24;
            code |= (t2<<base);
        }
        if(T==0){
            if(code%4 != 0)
                throw Error("illegal, I Memory address missaline");
            start = nowaddress = code;
        }
        else if(T==1) end = start+(code-1)*4;
        else{
            // printf("%d: 0x%08X\n",nowaddress, code);
            if(nowaddress>1020)
                throw Error("illegal, I-M loaded address is over 1024");
            inst[nowaddress/4] = code;
            // inst[nowaddress/4]->print();
            nowaddress += 4;
        }
        T++;
    }
    fclose(fp);

    this->PC = start;
}

void CPU::setReg(int address,int code){
    if(address == 0) return;
    // printf("set %d = %d\n",address, code);
    if( reg[address]!=code ){
        reg[address] = code;
        report.push_back( address );
    }
}

void CPU::printPC(){
    fprintf(fresult,"PC: 0x%08X\n", PC);
}

void CPU::printReport(int cycle){
    fprintf(fresult,"cycle %d\n",cycle);
    for(auto i:report){
        if(i==32) fprintf(fresult, "$HI: 0x%08X\n", reg[i]);
        else if(i==33) fprintf(fresult, "$LO: 0x%08X\n", reg[i]);
        else fprintf(fresult, "$%02d: 0x%08X\n",i,reg[i]);
    }
    printPC();
    report.clear();
    fprintf(fresult,"\n\n");
}


void CPU::runCycle(int cycle){

}
