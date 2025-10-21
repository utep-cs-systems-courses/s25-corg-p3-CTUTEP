.arch msp430g2553
.p2align 1,0
.text

.global state_cycle_asm
.extern state

; state_cycle_asm - increments the global byte 'state' and wraps modulo 5
state_cycle_asm:
    push   r15             ; save caller register
    mov.b  &state, r15     ; load current state (byte) into r15
    add    #1, r15         ; increment
    cmp    #5, r15         ; compare with 5
    jne    1f
    mov    #0, r15         ; wrap to 0
1:
    mov.b  r15, &state     ; store back to state
    pop    r15             ; restore
    ret