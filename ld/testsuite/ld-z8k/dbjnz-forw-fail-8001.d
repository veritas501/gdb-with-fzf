#name: Z8001 forward dbjnz just out of range
#source: dbjnz-opcode.s -z8001
#source: filler.s -z8001 --defsym NOPS=1
#source: branch-target2.s -z8001
#ld: -T reloc.ld -mz8001 -e 0
#error: .*: relocation truncated to fit: r_disp7 against `target2'
