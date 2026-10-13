; asm_05eb: store the page argument into the shared draw-page variable (c_0247)
_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        EXTRN   c_0247:WORD
        PUBLIC  _asm_05eb
_asm_05eb PROC  FAR
        push    bp
        mov     bp, sp
        mov     ax, [bp+6]
        mov     cs:c_0247, ax
        pop     bp
        retf
_asm_05eb ENDP
_TEXT   ENDS
        END
