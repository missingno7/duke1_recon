_TEXT SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        EXTRN   c_0247:WORD
        PUBLIC  _asm_053c
_asm_053c PROC FAR
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
        je      short page_done
        mov     cx, ax
        add     bx, 2000h
page_done:
        mov     dx, 03C4h
        mov     al, 2
        out     dx, al
        mov     cx, 8
row_loop:
        lodsb
        mov     dx, 03C5h
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
_asm_053c ENDP

page_io_wait PROC FAR
        push    bp
        mov     bp, sp
        push    ds
        push    di
        push    si
        mov     ax, 40h
        mov     es, ax
        mov     dx, es:[0063h]
        add     dl, 6
wait_retrace_low:
        in      al, dx
        test    al, 8
        jne     short wait_retrace_low
wait_retrace_high:
        in      al, dx
        test    al, 8
        je      short wait_retrace_high
        sub     dl, 6
        mov     ax, [bp+6]
        mov     bh, ah
        and     bh, 1
        mov     cl, 4
        shl     bh, cl
        mov     ah, al
        mov     al, 18h
        out     dx, ax
        mov     ah, 1Fh
        and     ah, 0EFh
        or      ah, bh
        mov     al, 7
        out     dx, ax
        pop     si
        pop     di
        pop     ds
        pop     bp
        retf
page_io_wait ENDP
_TEXT ENDS
        END
