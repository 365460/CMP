    lb $0, 0($s0)   # test for lb WriteTo0
    lb $0, 1($s0)
    lb $0, 2($s0)
    lb $0, 3($s0)
    lb $0, 4($s0)
    lb $t1, 0($s0)   # test for lb
    lb $t1, 1($s0)
    lb $t1, 2($s0)
    lb $t1, 3($s0)
    lb $t1, 4($s0)

    lbu $0, 0($s0)   # test for lb WriteTo0
    lbu $0, 1($s0)
    lbu $0, 2($s0)
    lbu $0, 3($s0)
    lbu $0, 4($s0)
    lbu $t1, 0($s0)   # test for lb
    lbu $t1, 1($s0)
    lbu $t1, 2($s0)
    lbu $t1, 3($s0)
    lbu $t1, 4($s0)

    lw $s0, 0($s0)
    sw $s0, 4($0)
    lw $t1, 4($0)

    addi $s0, $s0, 1
    sw $s0, 4($0)
    lw $t1, 4($0)

    addi $s1, $0, 1020
    sw $s0, 0($s1)

    addi $s1, $0, 200
    sw $s0, 0($s1)

    addi $s1, $0, 201
    sw $s0, 0($s1)    # err: Misalignment

    lw $s0, 0($s0)      # 11111111 11111111 01010101 10000000
    sh $s0, 4($0)       #
    lw $t1, 4($0)

    addi $s0, $s0, 83647
    sh $s0, 1022($0)
    lw $t1, 8($0)

    halt
    halt
    halt
