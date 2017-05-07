        ori $t0, $0, 32767
loop:   ori $t0, $t0, 32767
        bgtz $t0, loop

        addi $t0, $0, 32767
loop2:  addi $t0, $t0, -32768
        bgtz $t0, end
        j loop2
end:    halt
halt
halt
