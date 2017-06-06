#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    freopen("my4.S", "w", stdout);
    int n = 16;
    for(int i=0; i<n; i++){
        printf("lw $s0, %d($0)\n", i*16);
    }
}
