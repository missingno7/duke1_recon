; asm_029d: set VGA mode 1000h using the two byte parameters
_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        PUBLIC  _asm_029d
_asm_029d PROC  FAR
        push    bp
        mov     bp, sp
        mov     ax, 1000h
        mov     bl, byte ptr [bp+6]
        mov     bh, byte ptr [bp+8]
        int     10h
        pop     bp
        retf
_asm_029d ENDP
_TEXT   ENDS
        END
