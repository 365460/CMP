#include <iostream>
#include <cmath>
#include <cstdio>
#include <sstream>
using namespace std;
typedef unsigned int ll;
int getCode(int code,int a,int b){
    int res = 0;
    for(int i=a, j = 0; i<=b; i++,j++) if((code>>i)&1){
        res += (1<<j);
    }
    return res;
}
void print(int code){
    for(int i=31; i>=0; i--){
        if((code>>i)&1) cout << 1;
        else cout << 0;
    }
    cout << endl;
}
void parse(int code){
    int type = getCode(code,26, 31);
    int rs = getCode(code, 21, 25);
    int rt = getCode(code, 16, 20);
    int rd = getCode(code, 11, 15);
    int im = getCode(code,  0, 15);
    int funct = getCode(code, 0, 5);
    string name;
    if(type==0){
        if(funct==0x20) name = "ADD";
        if(funct==0x21) name = "ADDU";
        if(funct==0x22) name = "SUB";
        if(funct==0x24) name = "AND";
        if(funct==0x25) name = "OR";
        if(funct==0x26) name = "XOR";
        if(funct==0x27) name = "NOR";
        if(funct==0x28) name = "NAND";
        if(funct==0x2A) name = "SLT";
        if(funct==0x00) name = "SLL";
        if(funct==0x02) name = "SRL";
        if(funct==0x03) name = "SRA";
        if(funct==0x08) name = "JR";
        if(funct==0x18) name = "MULT";
        if(funct==0x19) name = "MULTU";
        if(funct==0x10) name = "MFHI";
        if(funct==0x12) name = "MFLO";
    }
    else{
        if(type==0x08) name = "ADDI";
        if(type==0x09) name = "ADDIU";
        if(type==0x23) name = "LW";
        if(type==0x21) name = "LH";
        if(type==0x25) name = "LHU";
        if(type==0x20) name = "LB";
        if(type==0x24) name = "LBU";
        if(type==0x2B) name = "SW";
        if(type==0x29) name = "SH";
        if(type==0x28) name = "SB";
        if(type==0x0F) name = "LUI";
        if(type==0x0C) name = "ANDI";
        if(type==0x0D) name = "ORI";
        if(type==0x0E) name = "NORI";
        if(type==0x0A) name = "SLTI";
        if(type==0x04) name = "BEQ";
        if(type==0x05) name = "BNE";
        if(type==0x07) name = "BGTZ";

        if(type==0x02) name = "J";
        if(type==0x03) name = "JAL";
        if(type==0x3F) name = "HALT";
    }
    if(type==0){
        cout << name << " $" << rd << " $" << rs << " $"<<rt << "  " <<  code << endl;
    }
    else
        cout << name << " $" << rt << " $" << rs << " " << im <<  " " << code << endl;
}
void turn(int x){
    for(int i=7; i>=0; i--)if((x>>i)&1){
        cout << "1";
    }
    else cout << 0;
    cout << " ";
}
int cal(int x){
    int ans = 0;
    for(int i=0; i<8; i++) if((x>>i)&1){
        ans += (1<<i);
    }
    return ans;
}
int main()
{
    // freopen("iimage.bin","rb",stdin);
    freopen("../../../archiTA/simulator/iimage.bin","rb",stdin);
    // freopen("../../../archiTA/testcase/open_testcase/fib_dp/iimage.bin","rb",stdin);
    freopen("inst.out","w",stdout);
    // freopen("myiimage.bin","rb",stdin);
    // freopen("binary2.out","w",stdout);
    char s[5];
    int T = 0;
    while(scanf("%c",&s[0])==1){
        for(int i=1; i<4; i++) scanf("%c",&s[i]);
        int re = 0;
        int base = 24;
        for(int j=0; j<4; j++, base -= 8){
            // int t2 = cal(s[j]); // cal(s[j]) == (unsigned)s[j]<<24>>24
            int t2 = (unsigned)s[j]<<24>>24;
            // cout << t2 << ", " << ((unsigned)s[j]<<24>>24) << endl;
            // int t2 = s[j];
            // int tmp = t2*(1<<base);
            re |= (t2<<base);
            // re += tmp;
            // turn(t2);
        }
        if(T==0){
            cout <<"PC  = " << re << endl;
        }
        else if(T==1){
             cout << "There are " << re << " instructions\n";
        }
        else{
            // printf("0x%08X",re);
            // cout << re ;
            // cout << endl;
            parse(re);
        }
        T++;
        int n;
        while(cin>>n){}
    }
    return 0;
}
/*
lhu $2, 0($0)        # $2 = x
op rs rt 0
37
32 24   23 16   15 8   7 0
*/
