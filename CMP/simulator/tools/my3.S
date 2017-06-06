jal next
next: addi $t0, $31, 16
    jr $t0
sb $31, 0($31)
lw $s2, 0($31)
add $s0, $s2, $31
addu $t0, $s0, $s2
sub $s0, $t0, $s0
and $t0, $t0, $s0
or $s0, $s0, $t0
xor $t0, $t0, $s0
nor $s0, $t0, $s0
nand $t0, $t0, $s0
slt $s0, $s0, $t0
sll $t0, $t0, $s0
srl $s0, $t0, $s0
sra $t0, $t0, $s0
mult $t0, $s0
mfhi $t0
multu $s0, $t0
mflo $s0
addi $t0, $s0, 1231
addiu $s0, $t0, 12333
sub $s0, $s0, $s0
sw $s0, 0($s0)
lw $s0, 0($s0)
lh $s0, 0($s0)
lhu $s0, 0($s0)
lb $s0, 0($s0)
lbu $s0, 0($s0)
sw $s0, 0($s0)
slti $t0, $s0, -324
sll $t0, $0, 0
lw $t0, 0($t0)
sub $t1, $t1, $t1
add $t0, $t0, $t0
beq $t1, $t1, next2
next2: sll $0, $0, 1
sll $0, $0, 0
sll $0, $10, 0

addi $s7, $0, 12
lw $t0, 0($s7)
lw $t1, 4($s7)

sb $t0, 4($s7)
jal print

sb $t0, 6($s7)
jal print

sb $t0, 7($s7)
jal print

sb $t0, 5($s7)
jal print

main:   lw $0, 0($0)
        addi $a0, $0, 125  # deep = 126
        jal fun1
        addi $s0, $v0, 0

        lw $a1, 0($0)
        addi $a0, $0, 62  # 83, 84>address overflow
        jal sum
        addi $s0, $v0, 0

        lw $t0, 0($0)
        lw $t0, 4($0)
        lw $t0, 8($0)

        addi $a0, $0, 120  # deep = 127
        jal fun1
        addi $s0, $v0, 0

        j end

fun1:   addi $sp, $sp, 8
        sw $ra, -4($sp)
        sw $a0, 0($sp)
        slti $t0, $a0, 1
        beq $t0, $0, L1     # $t0>1
        addi $v0, $0, 1
        addi $sp, $sp, -8
        jr $ra

L1:     addi $a0, $a0, -1
        jal fun1
        lw $a0, 0($sp)
        lw $ra, -4($sp)
        addi $sp, $sp, -8
        mult $v0, $a0
        mflo $v0
        jr $ra

sum:   addi $sp, $sp, 12
        sw $ra, -8($sp)
        sw $a1, -4($sp)
        sw $a0, 0($sp)
        slti $t0, $a0, 1
        beq $t0, $0, L2
        add $v0, $0, $a1
        addi $sp, $sp, -12
        jr $ra

L2:     addi $a0, $a0, -1
        jal sum
        lw $a0, 0($sp)
        lw $a1, -4($sp)
        lw $ra, -8($sp)
        addi $sp, $sp, -12
        add $v0, $t0, $a0
        jr $ra

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

end:    lb $s0, 1020($0)
        addi $s0, $s0, 1234
        sw $s0, 1020($0)
        sh $s0, 1022($0)
        sb $s0, 1023($0)
        lb $s0, 1023($0)
        lb $s0, 1020($0)
        add $s0, $s0, $s0
        sb $0, 997($0)
        lb $0, 996($0)
        addi $s0, 222
        sw $0, 996($0)
        ls $0, 996($0)
        sh $0, 1006($0)
        lw $s0, 0($0)
        lw $s0, 16($0)
        lw $s0, 32($0)
        lw $s0, 48($0)
        lw $s0, 64($0)
        lw $s0, 80($0)
        lw $s0, 96($0)
        lw $s0, 112($0)
        lw $s0, 128($0)
        lw $s0, 144($0)
        lw $s0, 160($0)
        lw $s0, 176($0)
        lw $s0, 192($0)
        lw $s0, 208($0)
        lw $s0, 224($0)
        lw $s0, 240($0)
        lw $s0, 256($0)
        addi $s0, $s0, 123
        sb $s0, 0($0)
        sb $s0, 300($0)
        lw $s0, 0($0)

halt
halt
halt
halt
halt
halt
halt
halt
halt
halt
