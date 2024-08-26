/**
 * Project Name: regex
 * Module Name: codegen/x64
 * Filename: mcode.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-27
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "../mcode.h"
#include "amd64.h"
#include "opcodes.h"
#include "registers.h"

uint32_t mcode_ranges(uint32_t lower_bounds, uint32_t upper_bounds, uint32_t n_ranges,
                      const Target *target) {
  uint8_t instr[32] = {};
  uint32_t instr_size = 0;
  // pseudo: mov   REREG_PATTERN1, <lower_bounds>
  instr_size = generateInstruction(instr, IOP_PRIME_MOV, IF2_G64_I64, REREG_PATTERN1, lower_bounds);
  // pseudo: mov   REREG_PATTERN2, <upper_bounds>
  // pseudo: setEveryBytes   xmm0, BYTE PTR [REREG_STR_PTR]
  while (n_ranges > 16) {
  // pseudo: load16bytes    xmm1, BYTE PTR [REREG_PATTERN1]
  // pseudo: load16bytes    xmm2, BYTE PTR [REREG_PATTERN2]
  // $match:
  // pseudo: cmp PER-BYTE LT  xmm1, xmm0, xmm1    // xmm1 =[BYTE] xmm0 < xmm1
  // pseudo: cmp PER-BYTE GT  xmm2, xmm0, xmm2    // xmm2 =[BYTE] xmm0 > xmm2
  // pseudo: or  PER-BYTE     xmm1, xmm1, xmm2    // xmm1 =[BYTE] xmm1 || xmm2
  // pseudo: test ALL ONE     xmm1                // in XMM registers, -1 means true and 0 means false
  // pseudo: jmp [FALSE]      $succeeded
  // pseudo: add              REREG_PATTERN1, 16
  // pseudo: add              REREG_PATTERN2, 16
  }
  return 0;
}

Array *mcode_char(char_t the_char) {
  // pseudo: test         <the_char>, BYTE PTR [REREG_STR_PTR]
  // pseudo: jmp [TRUE]   $succeeded
  return nullptr;
}

Array *mcode_plains(char_t *plains, uint32_t n_plains) {
  // pseudo: mov   REREG_PATTERN1, <plains>
  // pseudo: setEveryBytes   xmm0, BYTE PTR [REREG_STR_PTR]
  while (n_plains > 16) {
    // pseudo: load16bytes    xmm1, BYTE PTR [REREG_PATTERN1]
    // $match:
    // pseudo: cmp PER-BYTE EQ  xmm1, xmm0, xmm1    // xmm1 =[BYTE] xmm0 == xmm1
    // pseudo: test ALL ZERO    xmm1
    // pseudo: jmp [FALSE]      $succeeded
    // pseudo: add              REREG_PATTERN1, 16
  }
  return nullptr;
}

Array *mcode_sequence(char_t *plains, uint32_t n_plains) {
  // pseudo: mov   REREG_PATTERN1, <plains>
  // pseudo: mov   xmm0, BYTE PTR [REREG_STR_PTR]
  while (n_plains > 16) {
    // pseudo: load16bytes    xmm1, BYTE PTR [REREG_PATTERN1]
    // $match:
    // pseudo: cmp PER-BYTE EQ  xmm1, xmm0, xmm1    // xmm1 =[BYTE] xmm0 == xmm1
    // pseudo: test ALL ONE     xmm1
    // pseudo: jmp [FALSE]      $failed
    // pseudo: add              REREG_PATTERN1, 16
    // pseudo: add              REREG_STR_PTR, 16
  }
  return nullptr;
}
