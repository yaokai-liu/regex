/**
 * Project Name: regex
 * Module Name: codegen
 * Filename: regex-actions.c
 * Creator: Yaokai Liu
 * Create Date: 2024-07-20
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "regex-actions.h"
#include "mcode.h"
#include "target/target.h"

uint32_t Codegen_ranges(Range *ranges, uint32_t n_ranges, const Target *target) {
  Array *inst_array = target->instrBuffer;
  uint32_t lbs_offset = Array_length(target->rodataBuffer);
  for (uint32_t i = 0; i < n_ranges; i++) {
    Array_append(target->rodataBuffer, (void *) &ranges[i].min, 1);
  }
  uint32_t ubs_offset = Array_length(target->rodataBuffer);
  for (uint32_t i = 0; i < n_ranges; i++) {
    Array_append(target->rodataBuffer, (void *) &ranges[i].max, 1);
  }

  mcode_ranges((uint64_t) lbs_offset, (uint64_t) ubs_offset, n_ranges, target);
  return 0;
}

uint32_t Codegen_char(char_t the_char, bool inverse, const Target *target) {
  Array *inst_array = target->instrBuffer;
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

uint32_t Codegen_plains(char_t *plains, uint32_t n_plains, const Target *target) {
  Array *inst_array = target->instrBuffer;
  Array *mcode_array = mcode_plains(plains, n_plains);
  Array_append(inst_array, Array_get(mcode_array, 0), (int32_t) Array_length(mcode_array));
  uint32_t size = Array_length(mcode_array);
  Array_reset(mcode_array, nullptr);
  Array_destroy(mcode_array);
  return size;
}

uint32_t Codegen_charset(Charset *charset, const Target *target) {
  Array *range_array, *plain_array;
  Target *normal_target = Target_new(target->allocator),
         *inverse_target = Target_new(target->allocator);

  range_array = charset->parts[CT_NORMAL].ranges;
  plain_array = charset->parts[CT_NORMAL].ranges;
  Codegen_ranges(Array_get(range_array, 0), Array_length(range_array), normal_target);
  Codegen_plains(Array_get(plain_array, 0), Array_length(plain_array), normal_target);
  Target_concat(target, normal_target);
  // TODO: $$failed, jump to failed process program.
  // TODO: if normal part is matched, jump to $inverse_case
  // $inverse_case
  range_array = charset->parts[CT_INVERSE].ranges;
  plain_array = charset->parts[CT_INVERSE].ranges;
  Codegen_ranges(Array_get(range_array, 0), Array_length(range_array), inverse_target);
  Codegen_plains(Array_get(plain_array, 0), Array_length(plain_array), inverse_target);
  Target_concat(target, inverse_target);
  // $succeeded, make sp++

  return 0;
}

uint32_t Codegen_sequence(Array *sequence, const Target *target) {
  Array *inst_array = target->instrBuffer;
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
                            const Target *target) {
  Array *inst_array = target->instrBuffer;
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

uint32_t Codegen_branch(const Target *) {
  // TODO: fill address all should jump to failed: $failed
  return 0;
}

uint32_t Codegen_branches(const Target *) {
  // TODO: fill address all should jump to failed: $succeeded
  return 0;
}

uint32_t Codegen_group(const Target *, bool) {
  return 0;
}
