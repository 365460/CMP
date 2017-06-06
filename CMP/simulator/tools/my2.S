addi $s7, $0, 12
lw $t0, 0($s7)
lw $t1, 4($s7)
sb $t0, 4($s7)
jal print
sb $t0, 6($s7)
jal print
j end
print:  lw $s0, 4($0)
        lh $s1, 4($0)
        lh $s1, 6($0)
        lhu $s1, 4($0)
        lhu $s1, 6($0)
        lb $s1, 4($0)
        lb $s1, 5($0)
        lb $s1, 6($0)
        lb $s1, 7($0)
        lbu $s1, 4($0)
        lbu $s1, 5($0)
        lbu $s1, 6($0)
        lbu $s1, 7($0)
        jr $ra
end: halt
halt
halt
halt
halt
halt
halt
halt
halt
halt
