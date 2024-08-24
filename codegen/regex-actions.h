/**
 * Project Name: regex
 * Module Name: codegen
 * Filename: regex-actions.h
 * Creator: Yaokai Liu
 * Create Date: 2024-07-20
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#ifndef REGEX_REGEX_ACTIONS_H
#define REGEX_REGEX_ACTIONS_H

#include "target.h"
#include "target/target.h"

// elements of inst_array are supposed to be uint8_t.

// generate machine code of instruction from an array of Range.
// @return: the size of addend machine code.
uint32_t Codegen_ranges(Range *ranges, uint32_t n_ranges, const Target *target);

// generate machine code of instruction from a single character.
// @return: the size of addend machine code.
uint32_t Codegen_char(char_t the_char, bool inverse, const Target *target);

// generate machine code of instruction from a series of characters,
// which but match only one character.
// @return: the size of addend machine code.
uint32_t Codegen_plains(char_t *plains, uint32_t n_plains, const Target *target);

// generate machine code of instruction from a charset.
// @return: the size of addend machine code.
uint32_t Codegen_charset(Charset *charset, const Target *target);

// generate machine code of instruction from a sequence.
// @return: size of addend machine code.
uint32_t Codegen_sequence(Array *sequence, const Target *target);

// generate machine code of instruction from a quantified.
// @return: size of addend machine code.
uint32_t Codegen_quantified(Array *obj_inst_array, uint32_t loop_min, uint32_t loop_max,
                            const Target *target);

// generate machine code of instruction from a branch.
// @return: size of addend machine code.
uint32_t Codegen_branch(const Target *target);

// generate machine code of instruction from a branch array.
// @return: size of addend machine code.
uint32_t Codegen_branches(const Target *target);

// generate machine code of instruction from a group.
// @return: size of addend machine code.
uint32_t Codegen_group(const Target *target, bool inverse);

#endif  // REGEX_REGEX_ACTIONS_H
