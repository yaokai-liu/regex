/**
 * Project Name: regex
 * Module Name: codegen
 * Filename: instruction.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-20
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "instruction.h"
#ifdef TARGET_X64
  #include "x64/mcode.h"
#endif

uint32_t Codegen_ranges(Range *ranges, uint32_t n_ranges, Array *inst_array) {
  Array *lbs = Array_new(sizeof(char_t), Array_allocator(inst_array));
  Array *ubs = Array_new(sizeof(char_t), Array_allocator(inst_array));
  for (uint32_t i = 0; i < n_ranges; i++) {
    Array_append(lbs, (void *) &ranges[i].min, 1);
    Array_append(ubs, (void *) &ranges[i].max, 1);
  }
  Array *mc_array = mcode_ranges(Array_get(lbs, 0), Array_get(ubs, 0), n_ranges);
  Array_append(inst_array, Array_get(mc_array, 0), (int32_t) Array_length(mc_array));
  uint32_t size = Array_length(mc_array);
  Array_reset(lbs, nullptr);
  Array_reset(ubs, nullptr);
  Array_reset(mc_array, nullptr);
  Array_destroy(lbs);
  Array_destroy(ubs);
  Array_destroy(mc_array);
  return size;
}

uint32_t Codegen_char(char_t the_char, bool inverse, Array *inst_array) {
  Array *mcode_array = mcode_char(the_char);
  Array_append(inst_array, Array_get(mcode_array, 0), (int32_t) Array_length(mcode_array));
  if (inverse) {
    // TODO: jump to $$failed if not match
  }
  uint32_t size = Array_length(mcode_array);
  Array_reset(mcode_array, nullptr);
  Array_destroy(mcode_array);
  return size;
}

uint32_t Codegen_plains(char_t *plains, uint32_t n_plains, Array *inst_array) {
  Array *mcode_array = mcode_plains(plains, n_plains);
  Array_append(inst_array, Array_get(mcode_array, 0), (int32_t) Array_length(mcode_array));
  uint32_t size = Array_length(mcode_array);
  Array_reset(mcode_array, nullptr);
  Array_destroy(mcode_array);
  return size;
}

uint32_t Codegen_charset(Charset *charset, Array *inst_array) {
  Array *range_array, *plain_array;
  Array *normal_inst_array = Array_new(sizeof(uint8_t), Array_allocator(inst_array));
  Array *inverse_inst_array = Array_new(sizeof(uint8_t), Array_allocator(inst_array));

  range_array = charset->parts[CT_NORMAL].ranges;
  plain_array = charset->parts[CT_NORMAL].ranges;
  Codegen_ranges(Array_get(range_array, 0), Array_length(range_array), normal_inst_array);
  Codegen_plains(Array_get(plain_array, 0), Array_length(plain_array), normal_inst_array);
  // TODO: $$failed, jump to failed process program.
  // TODO: if normal part is matched, jump to $inverse_case
  // $inverse_case
  range_array = charset->parts[CT_INVERSE].ranges;
  plain_array = charset->parts[CT_INVERSE].ranges;
  Codegen_ranges(Array_get(range_array, 0), Array_length(range_array), inverse_inst_array);
  Codegen_plains(Array_get(plain_array, 0), Array_length(plain_array), inverse_inst_array);
  // $succeeded, make sp++

  return 0;
}

uint32_t Codegen_sequence(Array *sequence, Array *inst_array) {
  Array *mcode_array = mcode_sequence(Array_get(sequence, 0), Array_length(sequence));
  // if this is matched, jump to $$failed
  Array_append(inst_array, Array_get(mcode_array, 0), (int32_t) Array_length(mcode_array));
  // $succeeded, sp += Array_length(sequence);
  uint32_t size = Array_length(mcode_array);
  Array_reset(mcode_array, nullptr);
  Array_destroy(mcode_array);
  return size;
}

uint32_t Codegen_quantified(Array *obj_inst_array, uint32_t loop_min, uint32_t loop_max,
                            Array *inst_array) {
  uint32_t offset = Array_length(inst_array);
  // $entry
  // TODO: xor REREG_REPEAT, REREG_REPEAT
  // TODO: address fill back in obj_inst_array $internal_failed
  Array_append(inst_array, Array_get(obj_inst_array, 0), (int32_t) Array_length(obj_inst_array));
  if (loop_max > 0) {
    // TODO: cmp REREG_REPEAT, loop_max
    // TODO: jle $entry
  }
  // $internal_failed
  // TODO: quantified internal address fill back: $internal failed.
  if (loop_min > 0) {
    // TODO: cmp REREG_REPEAT, loop_max
    // TODO: jl $$failed
  }
  return 0;
}

uint32_t Codegen_branch(Array *) {
  // TODO: fill address all should jump to failed: $failed
  return 0;
}

uint32_t Codegen_branches(Array *) {
  // TODO: fill address all should jump to failed: $succeeded
  return 0;
}

uint32_t Codegen_group(Array *, bool) {
  return 0;
}
