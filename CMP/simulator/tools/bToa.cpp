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
    int im = getCode(code,  0, 15);
    cout << type << " " << rs << " " << rt << " " << im << endl;
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
    freopen("binary.out","w",stdout);
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
            printf("0x%08X",re);
            cout << endl;
            // parse(re);
        }
        T++;
    }
    return 0;
}
/*
lhu $2, 0($0)        # $2 = x
op rs rt 0
37
32 24   23 16   15 8   7 0
*/
