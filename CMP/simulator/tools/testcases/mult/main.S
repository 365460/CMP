lw $t0, 0($0)
lw $t1, 4($0)
mult $t0, $t1
mfhi $s2
mflo $s1
mult $t1, $t1
mfhi $s2
mflo $s1
mult $t0, $t0
mult $t0, $t0
mfhi $s2
mflo $s1
halt

    ; writeWord2File(2147483647, fp);
    ;
    ; //11111111 11110000 01010101 10000000
    ; writeWord2File(4293940608, fp);
