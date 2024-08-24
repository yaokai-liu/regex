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

typedef union {
  uint8_t value;
  struct {
    uint8_t lNibble : 4;
    uint8_t hNibble : 4;
  } form;
} Opcode;

Opcode generateOpcode();

#endif  // REGEX_OPCODES_H
