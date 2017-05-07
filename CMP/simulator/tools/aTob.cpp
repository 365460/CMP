#include <iostream>
#include <sstream>
#include <map>
#include <stdint.h>
#include <cstdio>
using namespace std;
#define DEGUG 1
map<string,int> Totype, Tohex;
map<string,int> func;
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
int parse(FILE *parsed, FILE *source){
    char s2[100];
    int Lineid = 0;
    while(fgets(s2,100, source)){
        string s(s2), tmp;
        if(s.size()==1) continue;
        stringstream ss(s);
        int now = 0;
        while(ss>>tmp){
            if(now==0 && tmp[ tmp.size()-1 ]==':'){
                tmp.pop_back();
                func[tmp] = Lineid;
                continue;
            }
            if(now==0){
                fprintf(parsed,"%s ", tmp.c_str());
            }
            else if(now==1){ // $a0,
                if(tmp[ tmp.size()-1] ==',' ) tmp.pop_back();
                fprintf(parsed,"%s ", tmp.c_str());
            }
            else if(now==2){
                if(tmp.find('(')!=std::string::npos){
                    string t[3];
                    int id = 0;
                    for(int i=0; i<tmp.size(); i++){
                        if(tmp[i]==')') break;
                        if(tmp[i]=='(') id++;
                        else t[id] += tmp[i];
                    }
                    /* the order is important */ // t C s ==> t s C
                    fprintf(parsed, "%s ", t[1].c_str());
                    fprintf(parsed, "%s ", t[0].c_str());
                    now = 4;
                }
                else {
                    if(tmp[ tmp.size()-1] == ',') tmp.pop_back();
                    fprintf(parsed,"%s ", tmp.c_str());
                }
            }
            else if(now==3){
                fprintf(parsed,"%s ", tmp.c_str());
            }
            now++;
        }
        fprintf(parsed,"\n");
        Lineid++ ;
    }
    return Lineid;
}
int toInt(string s){
    int ans = 0;
    stringstream ss;
    if(s[0]=='$'){
        if(s[1]>='0' && s[1]<='9'){
            for(int i=1; i<s.size(); i++)
                ans = ans*10 + s[i]-'0';
        }
        else ans = Tohex[s];
    }
    else if(s=="") ans = 0;
    else if((s[0]=='0' && s[1]=='x') ||
        (s[0]=='-'&&s[1]=='0'&&s[2]=='x') )
    {
        ss << std::hex << s;
        ss >> ans;
    }
    else{
        ss << s;
        ss >> ans;
    }
    return ans;
}
void print(int code){
    for(int i=31; i>=0; i--){
        if((code>>i)&1) cout << 1;
        else cout << 0;
    }
    cout << endl;
}
void putBinary(int s,int t,int v,int &code){
    for(int i=s,j=0; i<=t; i++,j++)if((v>>j)&1){
        code |= (1<<i);
    }
}
int getRtype(string rs, string rt, string rd,string C, int funct){
    // cout << rs << " " << rt << " " << rd << " " << C << " " << funct << endl;
    int code = 0;
    putBinary(21, 25, toInt(rs), code);
    putBinary(16, 20, toInt(rt), code);
    putBinary(11, 15, toInt(rd), code);
    putBinary(6,  10, toInt(C), code);
    putBinary(0,   5, funct, code);
    return code;
}
int getItype(int opcode, string rs, string rt, string C){
    // cout << opcode << " " << rs << " " << rt << " " << C << endl;
    int code = 0;
    putBinary(26, 31, opcode, code);
    putBinary(21, 25, toInt(rs), code);
    putBinary(16, 20, toInt(rt), code);
    putBinary(0,  15, toInt(C), code);
    return code;
}
int getJtype(int opcode, string C){
    int code = 0;
    putBinary(26, 31, opcode, code);
    putBinary(0,  25, toInt(C), code);
    return code;
}
int getCode(int code,int a,int b){
    int res = 0;
    for(int i=a, j = 0; i<=b; i++,j++) if((code>>i)&1){
        res += (1<<j);
    }
    return res;
}
void parseI(int code){
    int type = getCode(code,26, 31);
    int rs = getCode(code, 21, 25);
    int rt = getCode(code, 16, 20);
    int im = getCode(code,  0, 15);
    cout << type << " " << rs << " " << rt << " " << im << endl;
}
void parseR(int code){
    int type = getCode(code,26, 31);
    int rs = getCode(code, 21, 25);
    int rt = getCode(code, 16, 20);
    int rd = getCode(code, 11, 15);
    int c = getCode(code,  6, 10);
    int fu = getCode(code, 0, 5);
    cout << type << " " << rs << " " << rt << " " << rd << " " << c << " " << fu << endl;
}
void parseJ(int code){
    int type = getCode(code, 26, 31);
    int C = getCode(code, 0, 25);
    cout << type << " " << C << endl;
}
void init(){
    /* R type*/
    Totype["add"]  = Totype["addu"] = Totype["sub"]   = Totype["and"]  = 1;
    Totype["or"]   = Totype["xor"]  = Totype["nor"]   = Totype["nand"] = 1;
    Totype["slt"]  = Totype["sll"]  = Totype["srl"]   = Totype["sra"]  = 1;
    Totype["jr"]   = Totype["mult"] = Totype["multu"] = Totype["mfhi"] = 1;
    Totype["mflo"] = 1;

    Tohex["add"]  = 0x20, Tohex["addu"] = 0x21, Tohex["sub"]  = 0x22; Tohex["and"]  = 0x24;
    Tohex["or"]   = 0x25, Tohex["xor"]  = 0x26, Tohex["nor"]  = 0x27; Tohex["nand"] = 0x28;
    Tohex["slt"]  = 0x2A, Tohex["sll"]  = 0x00, Tohex["srl"]  = 0x02; Tohex["sra"]  = 0x03;
    Tohex["jr"]   = 0x08, Tohex["mult"] = 0x18, Tohex["multu"]= 0x19; Tohex["mfhi"] = 0x10;
    Tohex["mflo"] = 0x12;

    /* i-type*/
    Totype["addi"] = Totype["addiu"] =  Totype["lw"]   =  Totype["lh"]   = 2;
    Totype["lhu"]  = Totype["lb"]    =  Totype["lbu"]  =  Totype["sw"]   = 2;
    Totype["sh"]   = Totype["sb"]    =  Totype["lui"]  =  Totype["andi"] = 2;
    Totype["ori"]  = Totype["nori"]  =  Totype["slti"] =  Totype["beq"]  = 2;
    Totype["bne"]  = Totype["bgtz"]  =  2;

    Tohex["addi"] = 0x08, Tohex["addiu"] = 0x09, Tohex["lw"]  = 0x23, Tohex["lh"]   = 0x21;
    Tohex["lhu"]  = 0x25, Tohex["lb"]    = 0x20, Tohex["lbu"] = 0x24, Tohex["sw"]   = 0x2B;
    Tohex["sh"]   = 0x29, Tohex["sb"]    = 0x28, Tohex["lui"] = 0x0F, Tohex["andi"] = 0x0C;
    Tohex["ori"]  = 0x0D, Tohex["nori"]  = 0x0E, Tohex["slti"]= 0x0A, Tohex["beq"]  = 0x04;
    Tohex["bne"]  = 0x05, Tohex["bgtz"]  = 0x07;

    /* j-type*/
    Totype["j"] = Totype["jal"] = 3;

    Tohex["j"] = 0x02, Tohex["jal"] = 0x03;

    /* register */
    Tohex["$zero"] = 0,  Tohex["$at"] = 1,  Tohex["$v0"] = 2, Tohex["$v1"] = 3;
    Tohex["$a0"]   = 4,  Tohex["$a1"] = 5,  Tohex["$a2"] = 6, Tohex["$a3"] = 7;
    Tohex["$t0"]   = 8,  Tohex["$t1"] = 9,  Tohex["$t2"] =10, Tohex["$t3"] = 11;
    Tohex["$t4"]   = 12, Tohex["$t5"] = 13, Tohex["$t6"] =14, Tohex["$t7"] = 15;
    Tohex["$s0"]   = 16, Tohex["$s1"] = 17, Tohex["$s2"] =18, Tohex["$s3"] = 19;
    Tohex["$s4"]   = 20, Tohex["$s5"] = 21, Tohex["$s6"] =22, Tohex["$s7"] = 23;
    Tohex["$t8"]   = 24, Tohex["$t9"] = 25, Tohex["$k0"] =26, Tohex["$k1"] = 27;
    Tohex["$gp"]   = 28, Tohex["$sp"] = 29, Tohex["$fp"] =30, Tohex["$ra"] = 31;
    /*else*/
    Tohex[""] = 0x00;

}
int main()
{
    int PC_base = 336, Inst_num = 6;

    init();
    // FILE *fp = fopen("../../../archiTA/testcase/open_testcase/fib_dp/fib_dp.S","r");
    FILE *fp = fopen("my.S","r");
    FILE *fparsed = fopen("parsed.txt","w");
    Inst_num = parse(fparsed, fp);
    fclose(fparsed);
    fclose(fp);

    fparsed = fopen("parsed.txt", "r");
    FILE *fres = fopen("../iimage.bin","wb");

    writeWord2File(PC_base, fres);
    writeWord2File(Inst_num, fres);

    char s2[100];
    int id = 0;
    while(fgets(s2,100,fparsed)){
        string s(s2), tmp, op, rs, rt, rd, im, C, fu;
        int code;
        rs = rt = rd = C = fu = im = "";
        stringstream ss(s2);
        ss>>op;
        cout << PC_base + id*4 <<  " " ;
        if( Totype[op]== 1){ // R
            if(op=="sll" || op=="srl" || op=="sra"){
                ss >> rd;
                ss >> rt;
                ss >> C;
            }
            else if(op=="jr"){
                ss >> rs;
                if(rs[0]!='$') rs = to_string(func[rs]-id-1);
            }
            else if(op=="mult" || op=="multu"){
                ss >> rs;
                ss >> rt;
            }
            else if(op=="mfhi" || op=="mflo"){
                ss >> rd;
            }
            else{
                ss >> rd;
                ss >> rs;
                ss >> rt;
            }
            code = getRtype( rs, rt, rd, C, Tohex[op]);
            // parseR(code);
        }
        else if(Totype[op]==2){ // I
            if(op=="lui"){
                ss >> rt;
                ss >> C;
            }
            else if(op=="bgtz"){
                ss >> rs;
                ss >> C;
                C = to_string(func[C]-id-1);
            }
            else if(op=="beq" || op=="bne"){
                ss >> rs;
                ss >> rt;
                ss >> C;
                C = to_string(func[C]-id-1);
            }
            else{
                ss >> rt;
                ss >> rs;
                ss >> C;
            }
            code = getItype(Tohex[op], rs, rt, C);
            parseI(code);
        }
        else if(Totype[op]==3){ // J
            ss >> C;
            int offset = ((func[C]*4)+PC_base)/4;
            C = to_string(offset);
            code = getJtype(Tohex[op], C);
            parseJ(code);
        }
        else if(op=="halt"){
            code = 0xffffffff;
            // printf("S_Type : %d", code);
        }
        else code = 0;
        // printf("%2d %6s 0x%08X  %d\n",id+1,op.c_str(),code,624+id*4);
        printf("0x%08X\n",code);
        writeWord2File(code, fres);
        id++;
    }
    fclose(fres);
    fclose(fparsed);
    // int n;
    // while(cin>>n){}
    return 0;
}
