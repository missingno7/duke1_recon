; ProGraphx EGA/VGA Toolbox routines used by Duke Nukum (assembly unit, ASM_TEXT).
; Data tables at the start of the code segment, then the procedures in original order.
_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  CS:_TEXT
        PUBLIC  c_0247
        db      26 dup (0)              ; not referenced by the game
left_masks  db  0FFh, 7Fh, 3Fh, 1Fh, 0Fh, 07h, 03h, 01h
bit_masks   db  80h, 40h, 20h, 10h, 08h, 04h, 02h, 01h
        db      12 dup (0)              ; not referenced by the game
banner  db      23 dup (0Ah), 0Dh, 0Ah, 'Version 1.0 EGA/VGA'
        db      'ProGraphx EGA/VGA Toolbox', 0Dh, 0Ah, 1Ah
c_0247  dw      0                       ; read by every drawing routine
        db      01h, 00h, 00h, 00h, 00h, 27h, 00h, 00h, 00h, 0C7h, 00h, 00h, 00h, 3Fh, 01h
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
; asm_029d: set VGA mode 1000h using the two byte parameters
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
        je      short page_ready_0315
        add     dx, 0200h
page_ready_0315:
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
; asm_0424: write two planar glyph rows to VGA memory
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
        je      short page_ready_0424
        mov     cx, ax
        add     bx, 2000h
page_ready_0424:
        mov     dx, 03C4h
        mov     al, 2
        out     dx, al
        mov     cx, 10h
row_loop_0424:
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
        loop    row_loop_0424
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
row_loop_04c5:
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
        loop    row_loop_04c5
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
row_loop_053c:
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
        loop    row_loop_053c
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
; asm_05eb: store the page argument into the shared draw-page variable (c_0247)
        PUBLIC  _asm_05eb
_asm_05eb PROC  FAR
        push    bp
        mov     bp, sp
        mov     ax, [bp+6]
        mov     cs:c_0247, ax
        pop     bp
        retf
_asm_05eb ENDP
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
