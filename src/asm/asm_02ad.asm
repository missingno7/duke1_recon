_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        EXTRN   c_0247:WORD
        PUBLIC  _asm_02ad
_asm_02ad PROC  FAR
        push    bp
        mov     bp, sp
        push    ds
        push    di
        push    si
        mov     dx, 0A000h
        mov     ax, cs:c_0247
        cmp     al, 0
        je      short L_page_ready
        add     dx, 0200h
L_page_ready:
        mov     es, dx
        mov     dx, 0A400h
        mov     ds, dx
        mov     si, [bp+6]
        mov     di, [bp+8]
        mov     bx, 0026h
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        add     di, bx
        movsb
        movsb
        pop     si
        pop     di
        pop     ds
        pop     bp
        retf
_asm_02ad ENDP
_TEXT   ENDS
        END
