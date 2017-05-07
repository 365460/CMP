addi $t2, $t2, 4
lw $t0, 0($t2)
ori $t0, $t0, -234
sh $t0, 2($0)
lw $t0, 0($t2)
lh $t0, 0($t2)
lh $t0, 2($t2)

halt
