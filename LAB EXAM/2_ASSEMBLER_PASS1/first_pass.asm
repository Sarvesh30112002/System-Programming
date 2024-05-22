START:  MOV R1, R2
        ADD R1, R3
LOOP:   SUB R1, R4
        JNZ LOOP
        HLT
        MOV R2, R1
        ADD R3, R2
END:    HLT