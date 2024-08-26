/**
 * Project Name: regex
 * Module Name: codegen/x64
 * Filename: opcodes.h
 * Creator: Yaokai Liu
 * Create Date: 2024-08-24
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_OPCODES_H
#define REGEX_OPCODES_H

#ifndef __ORDER_LITTLE_ENDIAN__
  #error "Require little endian byte order."
#endif

#include <stdint.h>

uint32_t generateInstruction(uint8_t * dest, uint32_t instr_op, uint32_t instr_form, ...);

#endif  // REGEX_OPCODES_H
