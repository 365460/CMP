        addi $t0, $0, 32767
loop:   addiu $t0, $t0, 32767
        bgtz $t0, loop  # pos + pos ==> nagtive

        addi $t0, $0, 32767
loop2:  addiu $t0, $t0, -32768 # nagtive + nagtive ==> pos
        bgtz $t0, end
        j loop2
end:    halt
halt
halt
