main:   addi $a0, $0, 125
        jal fun1
        addi $s0, $v0, 0

        lw $a1, 0($0)
        addi $a0, $0, 62
        jal sum
        addi $s0, $v0, 0

        addi $a0, $0, 125   # address over
        jal fun1
        addi $s0, $v0, 0

        j end

fun1:   addi $sp, $sp, -8
        sw $ra, 4($sp)
        sw $a0, 0($sp)
        slti $t0, $a0, 1
        beq $t0, $0, L1
        addi $v0, $0, 1
        addi $sp, $sp, 8
        jr $ra
L1:     addi $a0, $a0, -1
        jal fact
        lw $a0, 0($sp)
        lw $ra, 4($sp)
        addi $sp, $sp, 8
        mult $v0, $a0
        mflo $v0
        jr $ra

sum:   addi $sp, $sp, -12
        sw $ra, 8($sp)
        sw $a1, 4($sp)
        sw $a0, 0($sp)
        slti $t0, $a0, 1
        beq $t0, $0, L2
        add $v0, $0, $a1
        addi $sp, $sp, 12
        jr $ra
L2:     addi $a0, $a0, -1
        jal fact
        lw $a0, 0($sp)
        lw $a1, 4($sp)
        lw $ra, 8($sp)
        addi $sp, $sp, 12
        add $v0, $t0, $a0
        jr $ra

end:  lw $t0, 0($0)
lw $t0, 4($0)
lw $t0, 8($0)
halt
