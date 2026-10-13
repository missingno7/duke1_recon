; asm_0424: write two planar glyph rows to VGA memory
_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        EXTRN   c_0247:WORD
        PUBLIC  _asm_0424
_asm_0424 PROC  FAR
        push    bp
        mov     bp, sp
        push    ds
        push    di
        push    si
        lds     si, [bp+6]
        mov     dx, 0A000h
        mov     es, dx
        mov     bx, [bp+0Ch]
        mov     ax, bx
        shl     ax, 1
        shl     ax, 1
        add     ax, bx
        shl     ax, 1
        shl     ax, 1
        shl     ax, 1
        mov     bx, [bp+0Ah]
        add     bx, ax
        mov     ax, cs:c_0247
        cmp     al, 0
        je      short page_ready
        mov     cx, ax
        add     bx, 2000h
page_ready:
        mov     dx, 03C4h
        mov     al, 2
        out     dx, al
        mov     cx, 10h
row_loop:
        mov     dx, 03CEh
        lodsb
        mov     ah, 8
        xchg    ah, al
        out     dx, ax
        mov     dx, 03C5h
        mov     al, 1
        out     dx, al
        lodsb
        xchg    es:[bx], al
        mov     al, 2
        out     dx, al
        lodsb
        xchg    es:[bx], al
        mov     al, 4
        out     dx, al
        lodsb
        xchg    es:[bx], al
        mov     al, 8
        out     dx, al
        lodsb
        xchg    es:[bx], al
        inc     bx
        mov     dx, 03CEh
        lodsb
        mov     ah, 8
        xchg    ah, al
        out     dx, ax
        mov     dx, 03C5h
        mov     al, 1
        out     dx, al
        lodsb
        xchg    es:[bx], al
        mov     al, 2
        out     dx, al
        lodsb
        xchg    es:[bx], al
        mov     al, 4
        out     dx, al
        lodsb
        xchg    es:[bx], al
        mov     al, 8
        out     dx, al
        lodsb
        xchg    es:[bx], al
        inc     bx
        add     bx, 26h
        loop    row_loop
        mov     al, 0Fh
        out     dx, al
        mov     dx, 03CEh
        mov     ax, 0FF08h
        out     dx, ax
        pop     si
        pop     di
        pop     ds
        pop     bp
        retf
_asm_0424 ENDP
_TEXT   ENDS
        END

