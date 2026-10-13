_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        PUBLIC  _asm_0258
_asm_0258 PROC  FAR
        push    bp
        mov     bp, sp
        mov     ax, [bp+6]
        cmp     al, 0
        jne     short L_0267
        mov     al, 0Dh
        jmp     short L_0274
L_0266:
        nop
L_0267:
        cmp     al, 1
        je      short L_0272
        xor     ah, ah
        mov     al, 12h
        jmp     short L_0274
L_0271:
        nop
L_0272:
        mov     al, 10h
L_0274:
        int     10h
        pop     bp
        retf

        push    bp
        mov     bp, sp
        mov     ax, [bp+6]
        xor     ah, ah
        int     10h
        pop     bp
        retf

        push    bp
        mov     bp, sp
        mov     ah, 10h
        mov     al, 1
        mov     bx, [bp+6]
        mov     bh, bl
        int     10h
        pop     bp
        retf

        mov     ah, 0Fh
        int     10h
        xor     ah, ah
        int     10h
        retf
_asm_0258 ENDP
_TEXT   ENDS
        END
