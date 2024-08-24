/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: reduce.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "action.h"
#include "allocator.h"
#include "array.h"
#include "reduce.gen.h"
#include "stack.h"
#include "target.h"
#include "terminal.h"
#include "tokens.gen.h"
#include "utils.h"
#include <stdint.h>
#include <string.h>

#define ALLOC_LEN 32

Branch *p_Branch_0(void *argv[], const Allocator * const allocator) {
  Branch *_arg0 = argv[0];
  Object *_arg1 = argv[1];
  Array_append(_arg0, _arg1, 1);
  allocator->free(_arg1);
  return _arg0;
}

Branch *p_Branch_1(void *argv[], const Allocator * const allocator) {
  Object *_arg0 = argv[0];
  Branch *br = Array_new(sizeof(Object), allocator);
  Array_append(br, _arg0, 1);
  allocator->free(_arg0);
  return br;
}

Charset *p_Charset_0(void *argv[], const Allocator * const allocator) {
  //    Terminal *_arg0 = argv[0];
  UnitArray *_arg1 = argv[1];
  //    Terminal *_arg2 = argv[2];

  Charset *charset = allocator->calloc(1, sizeof(Charset));

  // create parts
  charset->parts[CT_NORMAL].plains = Array_new(sizeof(char_t), allocator);
  charset->parts[CT_NORMAL].ranges = Array_new(sizeof(Range), allocator);
  charset->parts[CT_INVERSE].plains = Array_new(sizeof(char_t), allocator);
  charset->parts[CT_INVERSE].ranges = Array_new(sizeof(Range), allocator);

  uint32_t length = Array_length(_arg1);
  for (uint32_t i = 0; i < length; i++) {
    Unit *unit = Array_get(_arg1, i);
    if (unit->type == enum_Charset) {
      // select part
      struct charset_part *tap0 = &charset->parts[unit->inv];
      struct charset_part *tap1 = &charset->parts[!unit->inv];
      // copy without duplicate
      Charset *target = unit->target;
      Array_no_duplicated_concat(tap0->plains, target->parts[CT_NORMAL].plains);
      Array_no_duplicated_concat(tap0->ranges, target->parts[CT_NORMAL].ranges);
      Array_no_duplicated_concat(tap1->plains, target->parts[CT_INVERSE].plains);
      Array_no_duplicated_concat(tap1->ranges, target->parts[CT_INVERSE].ranges);
    } else if (unit->type == enum_CHAR) {
      // select part
      struct charset_part *tap = &charset->parts[unit->inv];
      // update plains
      char_t the_char = (char_t) (uint64_t) unit->target;
      Array_no_duplicated_append(tap->plains, &the_char, 1);
    } else if (unit->type == enum_Range) {
      // select part
      struct charset_part *tap = &charset->parts[unit->inv];
      // update range
      Range_array_update(tap->ranges, unit->target);
    } else {
      // never be touched
    }
  }
  releaseUnitArray(_arg1, allocator);
  Array_destroy(_arg1);
  return charset;
}

Sequence *p_Sequence_0(void *argv[], const Allocator * const allocator) {
  Terminal *_arg0 = argv[0];
  Sequence *seq = Array_new(sizeof(char_t), allocator);
  char_t the_char = (uint8_t) _arg0->value & 0xff;
  Array_append(seq, &the_char, 1);
  return seq;
}

Sequence *p_Sequence_1(void *argv[], const Allocator * const allocator) {
  Sequence *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  if (allocator) { argv[MAX_ARGC - 1] = "'-Wall' requires it be used, make the compiler happy."; }
  char_t the_char = (uint8_t) _arg1->value & 0xff;
  Array_append(_arg0, &the_char, 1);
  return _arg0;
}

Unit *p_Unit_0(void *argv[], const Allocator * const allocator) {
  Terminal *_arg0 = argv[0];
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_CHAR;
  unit->inv = false;
  unit->target = (void *) (uint64_t) _arg0->value;
  return unit;
}

Unit *p_Unit_1(void *argv[], const Allocator * const allocator) {
  Range *_arg0 = argv[0];
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Range;
  unit->inv = false;
  unit->target = (void *) _arg0;
  return unit;
}

Unit *p_Unit_2(void *argv[], const Allocator * const allocator) {
  Range *_arg0 = argv[0];
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Charset;
  unit->inv = false;
  unit->target = (void *) _arg0;
  return unit;
}

Unit *p_Unit_3(void *argv[], const Allocator * const allocator) {
  //  Terminal *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_CHAR;
  unit->inv = true;
  unit->target = (void *) (uint64_t) _arg1->value;
  return unit;
}

Unit *p_Unit_4(void *argv[], const Allocator * const allocator) {
  //  Range *_arg0 = argv[0];
  Range *_arg1 = argv[1];
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Charset;
  unit->inv = true;
  unit->target = (void *) _arg1;
  return unit;
}

UnitArray *p_UnitArray_0(void *argv[], const Allocator * const allocator) {
  UnitArray *_arg0 = argv[0];
  Unit *_arg1 = argv[1];
  Array_append(_arg0, _arg1, 1);
  allocator->free(_arg1);
  return _arg0;
}

UnitArray *p_UnitArray_1(void *argv[], const Allocator * const allocator) {
  Unit *_arg0 = argv[0];
  UnitArray *array = Array_new(sizeof(Unit), allocator);
  Array_append(array, _arg0, 1);
  allocator->free(_arg0);
  return array;
}

Group *p_Group_0(void *argv[], const Allocator *allocator) {
  //  Terminal *_arg0 = argv[0];
  Regexp *_arg1 = argv[1];
  //  Terminal *_arg2 = argv[2];
  Group *group = allocator->calloc(1, sizeof(Group));
  group->regexp = _arg1;
  return group;
}

Object *p_Object_0(void *argv[], const Allocator * const allocator) {
  Sequence *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Sequence;
  obj->inv = false;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_1(void *argv[], const Allocator * const allocator) {
  Charset *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Charset;
  obj->inv = false;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_2(void *argv[], const Allocator * const allocator) {
  Group *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Group;
  obj->inv = false;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_3(void *argv[], const Allocator * const allocator) {
  Quantified *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Quantified;
  obj->inv = false;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_4(void *argv[], const Allocator * const allocator) {
  //  Terminal *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = _arg1->type;
  obj->inv = true;
  obj->target = (void *) (uint64_t) _arg1->value;
  return obj;
}

Object *p_Object_5(void *argv[], const Allocator * const allocator) {
  //  Charset *_arg0 = argv[0];
  Charset *_arg1 = argv[1];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Charset;
  obj->inv = true;
  obj->target = _arg1;
  return obj;
}

Object *p_Object_6(void *argv[], const Allocator * const allocator) {
  //  Terminal *_arg0 = argv[0];
  Group *_arg1 = argv[1];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Group;
  obj->inv = true;
  obj->target = _arg1;
  return obj;
}

Quantified *p_Quantified_0(void *argv[], const Allocator * const allocator) {
  Object *_arg0 = argv[0];
  Quantifier *_arg1 = argv[1];
  Quantified *quantified = allocator->calloc(1, sizeof(Quantified));
  memcpy(&quantified->quant, _arg1, sizeof(Quantifier));
  memcpy(&quantified->object, _arg0, sizeof(Object));
  allocator->free(_arg0);
  allocator->free(_arg1);
  return quantified;
}

Quantifier *p_Quantifier_0(void *[], const Allocator * const allocator) {
  //    Terminal *_arg0 = argv[0];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 0;
  quant->max = 1;
  return quant;
}

Quantifier *p_Quantifier_1(void *[], const Allocator * const allocator) {
  //    Terminal *_arg0 = argv[0];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 1;
  quant->max = 0;
  return quant;
}

Quantifier *p_Quantifier_2(void *[], const Allocator * const allocator) {
  //    Terminal *_arg0 = argv[0];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 0;
  quant->max = 0;
  return quant;
}

Quantifier *p_Quantifier_3(void *argv[], const Allocator * const allocator) {
  //    Terminal *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  //    Terminal *_arg2 = argv[2];
  Terminal *_arg3 = argv[3];
  //    Terminal *_arg4 = argv[4];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = _arg1->value;
  quant->max = _arg3->value;
  return quant;
}

Quantifier *p_Quantifier_4(void *argv[], const Allocator * const allocator) {
  //    Terminal *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  //    Terminal *_arg2 = argv[2];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = _arg1->value;
  quant->max = _arg1->value;
  return quant;
}

Range *p_Range_0(void *argv[], const Allocator * const allocator) {
  Terminal *_arg0 = argv[0];
  //    Terminal *_arg1 = argv[1];
  Terminal *_arg2 = argv[2];
  Range *rng = allocator->calloc(1, sizeof(Range));
  rng->min = _arg0->value;
  rng->max = _arg2->value;
  return rng;
}

Regexp *p_Regexp_0(void *argv[], const Allocator * const allocator) {
  Regexp *_arg0 = argv[0];
  //    Terminal *_arg1 = argv[1];
  Branch *_arg2 = argv[2];
  Array_append(_arg0, _arg2, 1);
  allocator->free(_arg2);
  return _arg0;
}

Regexp *p_Regexp_1(void *argv[], const Allocator * const allocator) {
  Branch *_arg0 = argv[0];
  Regexp *regex = Array_new(sizeof_array, allocator);
  Array_append(regex, _arg0, 1);
  allocator->free(_arg0);
  return regex;
}

Regexp *p_Regexp_2(void *argv[], const Allocator * const allocator) {
  // since it's an empty rule.
  argv[MAX_ARGC - 1] = "'-Wall' requires it be used, make the compiler happy.";
  Regexp *regex = Array_new(sizeof_array, allocator);
  return regex;
}

Regexp *p___EXTEND_RULE__(void *argv[], const Allocator *) {
  Regexp *regex = argv[0];
  return regex;
}

Regexp *failed_to_get_next_state(Stack *state_stack, Stack *token_stack, void *result,
                                 uint32_t result_type, const Allocator *allocator);
Regexp *failed_to_produce(Stack *state_stack, Stack *token_stack, uint64_t *argv, uint32_t argc,
                          const Allocator *allocator);
Regexp *failed_to_get_action(Stack *state_stack, Stack *token_stack, const Allocator *allocator);

Regexp *failed_to_get_next_state(Stack *state_stack, Stack *token_stack, void *result,
                                 uint32_t result_type, const Allocator *allocator) {
  int32_t state = 0;
  Stack_top(state_stack, (int32_t *) &state, sizeof(int32_t));
  switch (result_type) {
    case enum_Regexp: {
      releaseRegexp(result, allocator);
      break;
    }
    case enum_Branch: {
      releaseBranch(result, allocator);
      break;
    }
    case enum_Group: {
      releaseGroup(result, allocator);
      break;
    }
    case enum_Object: {
      releaseObject(result, allocator);
      break;
    }
    case enum_Quantified: {
      releaseQuantified(result, allocator);
      break;
    }
    case enum_Charset: {
      releaseCharset(result, allocator);
      break;
    }
    case enum_Sequence: {
      releaseSequence(result, allocator);
      break;
    }
    case enum_UnitArray: {
      releaseUnitArray(result, allocator);
      break;
    }
    case enum_Unit: {
      releaseUnit(result, allocator);
      break;
    }
    default: {
    }
  }
  allocator->free(result);
  return failed_to_get_action(state_stack, token_stack, allocator);
}

Regexp *failed_to_produce(Stack *state_stack, Stack *token_stack, uint64_t *, uint32_t,
                          const Allocator *allocator) {
  // TODO： release memory allocated.
  return failed_to_get_action(state_stack, token_stack, allocator);
}

Regexp *failed_to_get_action(Stack *state_stack, Stack *token_stack, const Allocator *allocator) {
  // TODO： release memory allocated.
  Stack_clear(token_stack);
  Stack_clear(state_stack);
  allocator->free(token_stack);
  allocator->free(state_stack);
  return nullptr;
}
