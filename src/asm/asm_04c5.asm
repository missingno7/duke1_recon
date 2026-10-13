_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        EXTRN   c_0247:WORD
        PUBLIC  _asm_04c5
_asm_04c5 PROC  FAR
        push    bp
        mov     bp, sp
        push    ds
        push    di
        push    si
        lds     si, [bp+6]
        mov     dx, 0a000h
        mov     es, dx
        mov     bx, [bp+0ch]
        mov     ax, bx
        shl     ax, 1
        shl     ax, 1
        add     ax, bx
        shl     ax, 1
        shl     ax, 1
        shl     ax, 1
        mov     bx, [bp+0ah]
        add     bx, ax
        mov     ax, cs:c_0247
        cmp     al, 0
        je      no_page_adjust
        mov     cx, ax
        add     bx, 2000h
no_page_adjust:
        mov     dx, 03c4h
        mov     al, 2
        out     dx, al
        mov     cx, 8
row_loop:
        mov     dx, 03ceh
        lodsb
        mov     ah, 8
        xchg    ah, al
        out     dx, ax
        mov     dx, 03c5h
        mov     al, 1
        out     dx, al
        lodsb
        xchg    byte ptr es:[bx], al
        mov     al, 2
        out     dx, al
        lodsb
        xchg    byte ptr es:[bx], al
        mov     al, 4
        out     dx, al
        lodsb
        xchg    byte ptr es:[bx], al
        mov     al, 8
        out     dx, al
        lodsb
        xchg    byte ptr es:[bx], al
        add     bx, 28h
        loop    row_loop
        mov     al, 0fh
        out     dx, al
        mov     dx, 03ceh
        mov     ax, 0ff08h
        out     dx, ax
        pop     si
        pop     di
        pop     ds
        pop     bp
        retf
_asm_04c5 ENDP
_TEXT   ENDS
        END

