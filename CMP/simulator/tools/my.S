main:   lw $0, 0($0)

        lw $a1, 0($0)
        addi $a0, $0, 83  # deep = 84 ==> (2+1)*84 = 189
        jal sum
        addi $s0, $v0, 0

        j end

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
end: halt
