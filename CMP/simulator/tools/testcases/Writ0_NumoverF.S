lw $t1, 0($s0)      # $s0 = 2147483647
addiu $0, $t1 123   # err: WriteTo0
addi $0, $t1 123    # err: WriteTo0, NumOverF
halt
