/**
 * Project Name: regex
 * Module Name: codegen
 * Filename: instruction.h
 * Creator: Yaokai Liu
 * Create Date: 2024-07-20
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_INSTRUCTION_H
#define REGEX_INSTRUCTION_H

#include "target.h"

// elements of inst_array are supposed to be uint8_t.

// generate machine code of instruction from an array of Range.
// @return: the size of addend machine code.
uint32_t Codegen_ranges(Range *ranges, uint32_t n_ranges, Array *inst_array);

// generate machine code of instruction from a single character.
// @return: the size of addend machine code.
uint32_t Codegen_char(char_t the_char, bool inverse, Array *inst_array);

// generate machine code of instruction from a series of characters,
// which but match only one character.
// @return: the size of addend machine code.
uint32_t Codegen_plains(char_t *plains, uint32_t n_plains, Array *inst_array);

// generate machine code of instruction from a charset.
// @return: the size of addend machine code.
uint32_t Codegen_charset(Charset *charset, Array *inst_array);

// generate machine code of instruction from a sequence.
// @return: size of addend machine code.
uint32_t Codegen_sequence(Array *sequence, Array *inst_array);

// generate machine code of instruction from a quantified.
// @return: size of addend machine code.
uint32_t Codegen_quantified(Array *obj_inst_array, uint32_t loop_min, uint32_t loop_max,
                            Array *inst_array);

// generate machine code of instruction from a branch.
// @return: size of addend machine code.
uint32_t Codegen_branch(Array *br_inst_array);

// generate machine code of instruction from a branch array.
// @return: size of addend machine code.
uint32_t Codegen_branches(Array *inst_array);

// generate machine code of instruction from a group.
// @return: size of addend machine code.
uint32_t Codegen_group(Array *inst_array, bool inverse);

#endif  // REGEX_INSTRUCTION_H
