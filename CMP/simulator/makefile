GCC:= g++
Flag:= -std=c++11

main: main.cpp CPU.o Inst.o
	$(GCC) $(Flag) CPU.o Error.o Inst.o DS.o Cache.o Mem.o PGT.o TLB.o main.cpp -o CMP

Error.o: Error.cpp Error.h
	$(GCC) $(Flag) -c Error.cpp -o Error.o

CPU.o: CPU.cpp CPU.h Error.o DS.o
	$(GCC) $(Flag) -c CPU.cpp -o CPU.o

Inst.o: Instruction.h Instruction.cpp CPU.o Error.o
	$(GCC) $(Flag) -c Instruction.cpp -o Inst.o

DS.o: Cache.o Mem.o PGT.o TLB.o DataSystem.cpp DataSystem.h
	$(GCC) $(Flag) -c DataSystem.cpp -o DS.o

Cache.o: Cache.h Cache.cpp
	$(GCC) $(Flag) -c Cache.cpp -o Cache.o

Mem.o: Memory.cpp Memory.h Cache.o
	$(GCC) $(Flag) -c Memory.cpp -o Mem.o

PGT.o: PGT.h PGT.cpp
	$(GCC) $(Flag) -c PGT.cpp -o PGT.o

TLB.o: TLB.h TLB.cpp
	$(GCC) $(Flag) -c TLB.cpp -o TLB.o

run:main
	./CMP

clean:
	rm *.o CMP.exe *.rpt
