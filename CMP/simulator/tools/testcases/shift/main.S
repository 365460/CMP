lw $t0, 0($0)
sll $t1, $t0, 1
sll $t1, $t0, 2
srl $t1, $t0, 2
sra $t1, $t0, 2
halt

; 11111111 11110000 01010101 10000000
; writeWord2File(4293940608, fp);
