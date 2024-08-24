/**
 * Project Name: regex
 * Module Name: codegen/x64/machine
 * Filename: opcodes.c
 * Creator: Yaokai Liu
 * Create Date: 2024-08-24
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "opcodes.h"

Opcode generateOpcode() {
  Opcode opcode = {};
  opcode.form.hNibble = 0;
  return opcode;
}
