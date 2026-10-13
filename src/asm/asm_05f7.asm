_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        PUBLIC  _asm_05f7
_asm_05f7 PROC  FAR
        push    bp
        mov     bp, sp
        mov     ax, [bp+6]
        mov     ah, 5
        int     10h
        pop     bp
        retf
_asm_05f7 ENDP
_TEXT   ENDS
        END
