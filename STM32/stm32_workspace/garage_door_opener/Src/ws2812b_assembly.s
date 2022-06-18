/*
 * ws2812b_assembly.s
 *
 *  Created on: Mar 31, 2021
 *      Author: spud
 */

#if 0
  .syntax unified

  .global output_ws2812b
  .extern _vectors

  .section .init, "ax"
  .thumb_func

// WS2812 Cortex M0+ code

// output_ws2812b(uint8_t * pbuf, uint32_t count);
// optionally: output_ws2812b(uint8_t * pbuf, uint32_t count, uint32_t gpio_mask);

// '1' bit: 8 clocks hi, 4 clocks lo
// '0' bit: 4 clocks hi, 8 clocks lo
// recommended cpu clock: 12 MHz

// R0 = (param 1) byte buffer address
// R1 = (param 2) byte count
// R2 = FGPIO port bit (could be passed as param 3)
// R3 = data bytes
// R4 = data bit mask (must be saved and restored)
// R5 = FGPIO port base (must be saved and restored)
// R6 = #1, for rors instruction

  .equ  FGPIOA_BASE,  0xF8000000        // fast IO
  .equ  PSOR,         0x4               // output set register offset
  .equ  PCOR,         0x8               // output clear register offset
  .equ  PTB2,         1<<10             // gpio output bit (next to the GND pin)
  .equ  MASK,         0x80808080        // never-ending bit mask (8 LSBs are what count)

output_ws2812b:
    push   {r4-r6}                 // need to preserve all above r0-r3
    add    r0,r1                   // point r0 to end of data + 1
    rsbs   r1,r1,#0                // negate byte count
    ldr    r2,=PTB2                // using this bit for our output
    ldrb   r3,[r0,r1]              // load r3 with data byte [r0+r1]
    ldr    r4,=MASK                // endless data bit mask, so no reloading (output data in MSB->LSB order)
    ldr    r5,=FGPIOA_BASE         // pointer to FGPIO
    movs   r5,#1                   // mask rotate count
    cpsid  i                       // disable ints (may want to save and restore state later)

L0: str    r2,[r5,PSOR]            // set output to 1
    tst    r3,r4                   // check state of current bit
    beq    ZBit                    // branch if bit is 0 (shorter 1-time)

    rors    r4,r6                  // shift mask bit right
    bcc     L1                     // no new byte, finish '1' bit

    adds   r1,#1                   // advance to new byte
    ldrb   r3,[r0,r1]              // load r3 with new byte [r0+r1]
    str    r2,[r5,PCOR]            // set output to 0
    beq    Done                    // (Z holds result of the adds instruction)
    b      L0                      // more bytes

L1: nop
    nop
    str    r2,[r5,PCOR]            // set output to 0
    nop
    b      L0                      // next bit

ZBit:
    str    r2,[r5,PCOR]            // set output to 0
    rors   r4,r6                   // shift mask bit right
    bcc    L2                      // no new byte, finish '0' bit

    adds   r1,#1                   // advance to new byte
L2: ldrb   r3,[r0,r1]              // load r3 with byte [r0+r1] (just a delay if not a new byte)
    bne    L0                      // more bytes (if we jumped over adds, beq taken because r4 != 0)

Done:
    cpsie  i                       // enable ints (may want to save and restore state later)
    pop   {r4-r6}
    bx    lr                       // return

#endif
