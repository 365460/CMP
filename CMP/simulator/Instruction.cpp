#include "Instruction.h"
#include <map>
#include <iostream>

int ADD(int a,int b,CPU *cpu){
    int c = a+b;
    if(a<0 && b<0 && c>=0) cpu->err.addError(NumOverF);
    if(a>0 && b>0 && c<=0) cpu->err.addError(NumOverF);

    return c;
}
int getCode(int code,int a,int b){  // get a to b
    int res = 0;
    for(int i=a, j = 0; i<=b; i++,j++) if((code>>i)&1){
        res += (1<<j);
    }
    return res;
}
/*                  init Instruction::Totype (for decode)                */
std::map<int,int> Instruction::buildMap(){
    std::map<int,int> Totype;
/* R-type */
    Totype[0x00] = R_Type;

/* I-type */
    Totype[0x08] = Totype[0x09] =  Totype[0x23] = Totype[0x21] = I_Type;
    Totype[0x25] = Totype[0x20] =  Totype[0x24] = Totype[0x2B] = I_Type;
    Totype[0x29] = Totype[0x28] =  Totype[0x0F] = Totype[0x0C] = I_Type;
    Totype[0x0D] = Totype[0x0E] =  Totype[0x0A] = Totype[0x04] = I_Type;
    Totype[0x05] = Totype[0x07] =  I_Type;

/* J-type*/
    Totype[0x02] = Totype[0x03] = J_Type;

    return Totype;
}
std::map<int,int> Instruction::Totype = Instruction::buildMap();


Instruction* decode(int code){
    int opcode = getCode(code, 26, 31);
    switch(Instruction::Totype[ opcode ]){
        case R_Type:
            return new Inst_R(code);
        case I_Type:
            return new Inst_I(code);
        case J_Type:
            return new Inst_J(code);
        default:
            return new Inst_S(code);
    }
}
/*          R-type          */
Inst_R::Inst_R(){}

Inst_R::Inst_R(int code){
    this->code = code;
    opcode = getCode(code,26, 31);
    rs = getCode(code, 21, 25);
    rt = getCode(code, 16, 20);
    rd = getCode(code, 11, 15);
    C = getCode(code,  6, 10);
    funct = getCode(code, 0, 5);
}

void Inst_R::run(CPU *cpu){
    if(funct==0x20){ // add
        if(rd==0) cpu->err.addError(WriteTo0);
        int c = ADD(cpu->reg[rs], cpu->reg[rt], cpu);
        cpu->setReg(rd, c);
    }
    else if(funct==0x21){ //addu
        if(rd==0) cpu->err.addError(WriteTo0);
        int a = cpu->reg[rs], b = cpu->reg[rt], c= a+b;
        cpu->setReg(rd, c);
    }
    else if(funct==0x22){ //sub
        if(rd==0) cpu->err.addError(WriteTo0);
        int c = ADD(cpu->reg[rs], -cpu->reg[rt], cpu);
        cpu->setReg(rd, c);
    }
    else if(funct==0x24){ // and
        if(rd==0) cpu->err.addError(WriteTo0);
        cpu->setReg(rd, cpu->reg[rs]&cpu->reg[rt]);
    }
    else if(funct==0x25){ // or
        if(rd==0) cpu->err.addError(WriteTo0);
        cpu->setReg(rd, cpu->reg[rs]|cpu->reg[rt]);
    }
    else if(funct==0x26){ // xor
        if(rd==0) cpu->err.addError(WriteTo0);
        cpu->setReg(rd, cpu->reg[rs]^cpu->reg[rt]);
    }
    else if(funct==0x27){ // nor
        if(rd==0) cpu->err.addError(WriteTo0);
        cpu->setReg(rd, ~(cpu->reg[rs] | cpu->reg[rt]) );
    }
    else if(funct==0x28){ // nand
        if(rd==0) cpu->err.addError(WriteTo0);
        cpu->setReg(rd, ~(cpu->reg[rs] & cpu->reg[rt]) );
    }
    else if(funct==0x2A){ // slt
        if(rd==0) cpu->err.addError(WriteTo0);
        bool v = cpu->reg[rs] < cpu->reg[rt];
        cpu->setReg(rd, v);
    }
    else if(funct==0x00){ // sll
        if( !(rd==0 && rt==0 && C==0) && rd==0) cpu->err.addError(WriteTo0);
        cpu->setReg(rd, cpu->reg[rt]<<C);
    }
    else if(funct==0x02){ // srl
        if(rd==0) cpu->err.addError(WriteTo0);
        cpu->setReg(rd, (unsigned)cpu->reg[rt]>>C);
    }
    else if(funct==0x03){ // sra
        if(rd==0) cpu->err.addError(WriteTo0);
        cpu->setReg(rd, cpu->reg[rt]>>C);
    }
    else if(funct==0x08){ // jr
        cpu->PC =  cpu->reg[rs];
    }
    else if(funct==0x18){ // muti
        if(!cpu->hadgethi)  cpu->err.addError(OverWriteHI);
        cpu->hadgethi = false;

        long long ans = (long long)cpu->reg[rs] *
                        (long long)cpu->reg[rt];
        int hi = ans>>32,  lo = ans & 0x00000000FFFFFFFF;
        cpu->setReg(32, hi);
        cpu->setReg(33, lo);
    }
    else if(funct==0x19){ //multu
        if(!cpu->hadgethi)  cpu->err.addError(OverWriteHI);
        cpu->hadgethi = false;

        unsigned long long ans = (unsigned long long)(unsigned)cpu->reg[rs] *
                        (unsigned long long)(unsigned)cpu->reg[rt];
        int hi = ans>>32,  lo = ans & 0x00000000FFFFFFFF;
        cpu->setReg(32, hi);
        cpu->setReg(33, lo);

    }
    else if(funct==0x10){ //mfhi
        cpu->hadgethi = true;
        if(rd==0) cpu->err.addError(WriteTo0);
        else cpu->setReg(rd, cpu->reg[32]);
    }
    else if(funct==0x12){ // mflo
        cpu->hadgethi = true;
        if(rd==0) cpu->err.addError(WriteTo0);
        else cpu->setReg(rd, cpu->reg[33]);
    }
    else throw Error("Unknown instruction");
}

void Inst_R::print(){
    printf("R_type : %d %d %d %d %d\n", rs, rt, rd, C, funct);
}

/*          I-type          */
Inst_I::Inst_I(){}

Inst_I::Inst_I(int code){
    this->code = code;
    opcode = getCode(code,26, 31);
    rs = getCode(code, 21, 25);
    rt = getCode(code, 16, 20);
    C = code<<16>>16;
}

void Inst_I::run(CPU *cpu){

    if(opcode==0x08){ // addi
        if(rt==0) cpu->err.addError(WriteTo0);
        int c = ADD(cpu->reg[rs], C, cpu);

        cpu->setReg(rt, c);
    }
    else if(opcode==0x09){ // addiu
        if(rt==0) cpu->err.addError(WriteTo0);
        else cpu->setReg(rt, cpu->reg[rs] + C);
    }
    else if(opcode==0x23){ // lw
        if(rt==0) cpu->err.addError(WriteTo0);

        unsigned int address = ADD(cpu->reg[rs],C,cpu);
        if(address>1020) cpu->err.addError(MemAddOverF);
        if(address%4!=0) cpu->err.addError(DataMisaligned);
        if(cpu->err.halt) return;

        cpu->setReg(rt, cpu->memory[address/4] );
    }
    else if(opcode==0x21){ // lh
        if(rt==0)  cpu->err.addError(WriteTo0);

        unsigned int address = ADD(cpu->reg[rs],C,cpu);
        if(address>1022) cpu->err.addError(MemAddOverF);
        if(address%2!=0) cpu->err.addError(DataMisaligned);
        if(cpu->err.halt) return;

        int value = cpu->memory[ address/4 ];
        if(address%4==0) value = value>>16; // front
        else value = value << 16 >> 16;
        cpu->setReg(rt, value );
    }
    else if(opcode==0x25){ // lhu
        if(rt==0) cpu->err.addError(WriteTo0);

        unsigned int address = ADD(cpu->reg[rs],C,cpu);
        if(address>1022) cpu->err.addError(MemAddOverF);
        if(address%2!=0) cpu->err.addError(DataMisaligned);
        if(cpu->err.halt) return;

        int value = cpu->memory[ address/4 ];
        if(address%4==0) value = (unsigned)value>>16; // front
        else value = (unsigned)value << 16 >> 16;
        cpu->setReg(rt, value );
    }
    else if(opcode==0x20){ //lb
        if(rt==0) cpu->err.addError(WriteTo0);

        unsigned int address = ADD(cpu->reg[rs],  C, cpu);
        if(address>1023) cpu->err.addError(MemAddOverF);
        if(cpu->err.halt) return;

        int value = cpu->memory[address/4];
        if(address%4==0) value = value>>24;
        else if(address%4==1) value = value<<8>>24;
        else if(address%4==2) value = value<<16>>24;
        else value = value<<24>>24;

        cpu->setReg(rt, value);
    }
    else if(opcode==0x24){ //lbu
        if(rt==0) cpu->err.addError(WriteTo0);

        unsigned int address = ADD(cpu->reg[rs] , C ,cpu);
        if(address>1023) cpu->err.addError(MemAddOverF);
        if(cpu->err.halt) return;

        int value = cpu->memory[address/4];
        if(address%4==0) value = (unsigned)value>>24;
        else if(address%4==1) value = (unsigned)value<<8>>24;
        else if(address%4==2) value = (unsigned)value<<16>>24;
        else value = (unsigned)value<<24>>24;

        cpu->setReg(rt, value);
    }
    else if(opcode==0x2B){ //sw
        unsigned int address = ADD(cpu->reg[rs],C,cpu);
        if(address>1020) cpu->err.addError(MemAddOverF);
        if(address%4!=0) cpu->err.addError(DataMisaligned);
        if(cpu->err.halt) return;

        unsigned int value = cpu->reg[rt];
        cpu->memory[address/4] = value;
    }
    else if(opcode==0x29){ //sh
        unsigned int address = ADD(cpu->reg[rs],C, cpu);
        if(address>1022) cpu->err.addError(MemAddOverF);
        if(address%2!=0) cpu->err.addError(DataMisaligned);
        if(cpu->err.halt) return;

        unsigned int value = cpu->reg[rt] & 0x0000FFFF;
        unsigned int now = cpu->memory[address/4];
        if(address%4==0){
            now = now<<16>>16;
            now |= value<<16;
        }
        else{
            now = now>>16<<16;
            now |= value;
        }
        cpu->memory[address/4] = now;
    }
    else if(opcode==0x28){ //sb
        unsigned int address = ADD(cpu->reg[rs],C, cpu);
        if(address>1023) cpu->err.addError(MemAddOverF);
        if(cpu->err.halt) return;

        unsigned int value = (unsigned) cpu->reg[rt] & 0x000000FF;
        unsigned int now = cpu->memory[address/4];
        int index = address%4, start = (4-index-1)*8;
        for(int i=0; i<8; i++, start++){
            if((value>>i)&1 && !((now>>start)&1)) now |= (1<<(start));
            else if( !((value>>i)&1) && (now>>start)&1) now ^= (1<<(start));
        }
        cpu->memory[address/4] = now;
    }
    else if(opcode==0x0F){ //lui
        if(rt==0) cpu->err.addError(WriteTo0);
        int result = C<<16;
        cpu->setReg(rt, result);
    }
    else if(opcode==0x0C){ //andi
        if(rt==0) cpu->err.addError(WriteTo0);
        int cc = (unsigned) C<<16>>16;
        int result = cpu->reg[rs]&cc;
        cpu->setReg(rt, result);
    }
    else if(opcode==0x0D){ //ori
        if(rt==0) cpu->err.addError(WriteTo0);
        int cc = (unsigned) C<<16>>16;
        int result = cpu->reg[rs]|cc;
        cpu->setReg(rt, result);
    }
    else if(opcode==0x0E){ //nori
        if(rt==0) cpu->err.addError(WriteTo0);
        int cc = (unsigned) C<<16>>16;
        int result = ~(cpu->reg[rs]|cc);
        cpu->setReg(rt, result);
    }
    else if(opcode==0x0A){ //slti
        if(rt==0) cpu->err.addError(WriteTo0);
        int result = cpu->reg[rs] < C;
        cpu->setReg(rt, result);
    }
    else if(opcode==0x04){ //beq
        if(cpu->reg[rs]==cpu->reg[rt]){
            cpu->PC = ADD(cpu->PC, C*4, cpu);
        }
    }
    else if(opcode==0x05){ //bne
        if(cpu->reg[rs]!=cpu->reg[rt]){
            cpu->PC = ADD(cpu->PC, C*4, cpu);
        }
    }
    else if(opcode==0x07){ //bgtz
        if(cpu->reg[rs]>0){
            cpu->PC = ADD(cpu->PC, C*4, cpu);
        }
    }
    else throw Error("Unknown instruction");
}

void Inst_I::print(){
    printf("I_type : %d %d %d %d\n", opcode, rs, rt, C);
}

/*          J-type          */
Inst_J::Inst_J(){}

Inst_J::Inst_J(int code){
    this->code = code;
    opcode = getCode(code, 26, 31);
    C = getCode(code, 0, 25);
}

void Inst_J::run(CPU *cpu){
    if(opcode==0x02){ // j
        cpu->PC = C*4;
    }
    else if(opcode==0x03){ // jal
        cpu->setReg(31, cpu->PC);
        cpu->PC = C*4;
    }
    else throw Error("Unknown instruction");
}

void Inst_J::print(){
    printf("J_type : %d %d\n", opcode, C);
}


/*          S-type          */
Inst_S::Inst_S(){}

Inst_S::Inst_S(int code){
    this->code = code;
    opcode = getCode(code, 26, 31);
}

void Inst_S::run(CPU *cpu){

    if(opcode == 0x3F){ // halt
        cpu->err.addError(Halt);
    }
    else throw Error("Unknown instruction");
}
void Inst_S::print(){
    printf("S_type : %d\n", opcode);
}
