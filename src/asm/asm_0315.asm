_TEXT SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        EXTRN   c_0247:WORD
        PUBLIC  _asm_0315
_asm_0315 PROC FAR
        push    bp
        mov     bp, sp
        push    ds
        push    di
        push    si
        mov     dx, 0A000h
        mov     ax, word ptr cs:c_0247
        cmp     al, 0
        je      short page_ready
        add     dx, 0200h
page_ready:
        mov     es, dx
        mov     ds, dx
        mov     bx, [bp+8]
        mov     ax, bx
        shl     ax, 1
        shl     ax, 1
        add     ax, bx
        shl     ax, 1
        shl     ax, 1
        shl     ax, 1
        mov     bx, [bp+6]
        add     ax, bx
        add     ax, 0050h
        mov     di, ax
        sub     ax, 0078h
        sub     ax, [bp+0Ah]
        mov     si, ax
        mov     bx, 0026h
        mov     ax, 0052h
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        add     di, bx
        sub     si, ax
        movsb
        movsb
        pop     si
        pop     di
        pop     ds
        pop     bp
        retf
        push    bp
        mov     bp, sp
        push    ds
        push    di
        push    si
        mov     dx, 03DAh
wait_clear:
        in      al, dx
        and     al, 8
        jne     short wait_clear
wait_set:
        in      al, dx
        and     al, 8
        je      short wait_set
        pop     si
        pop     di
        pop     ds
        pop     bp
        retn
_asm_0315 ENDP
_TEXT ENDS
        END
