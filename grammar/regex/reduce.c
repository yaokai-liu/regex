/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: reduce.c
 * Creator: Yaokai Liu
 * Create Date: 2024-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "array.h"
#include "enum.h"
#include "generated/regex/reduce.gen.h"
#include "generated/tokens.gen.h"
#include "stack.h"
#include "target.h"
#include "terminal.h"
#include "utils.h"
#include <stdint.h>
#include <string.h>

#define ALLOC_LEN 32

Branch *p_Branch_0(Token argv[], RegexContext *, const Allocator * const allocator) {
  Branch *_arg0 = argv[0].value;
  Object *_arg1 = argv[1].value;
  Array_append(_arg0, _arg1, 1);
  allocator->free(_arg1);
  return _arg0;
}

Branch *p_Branch_1(Token argv[], RegexContext *, const Allocator * const allocator) {
  Object *_arg0 = argv[0].value;
  Branch *br = Array_new(sizeof(Object), enum_Object, allocator);
  Array_append(br, _arg0, 1);
  allocator->free(_arg0);
  return br;
}

Charset *p_Charset_0(Token argv[], RegexContext *, const Allocator * const allocator) {
  UnitArray *_arg1 = argv[1].value;

  Charset *charset = allocator->calloc(1, sizeof(Charset));
  // create parts
  charset->parts[CT_NORMAL].plains  = Set_new(enum_CHAR,  nullptr, allocator);
  charset->parts[CT_NORMAL].ranges  = Set_new(enum_Range, nullptr, allocator);
  charset->parts[CT_INVERSE].plains = Set_new(enum_CHAR,  nullptr, allocator);
  charset->parts[CT_INVERSE].ranges = Set_new(enum_Range, nullptr, allocator);

  uint32_t length = Array_length(_arg1);
  Unit *units = Array_first_real(_arg1);
  for (uint32_t i = 0; i < length; i++) {
    Unit *unit = &units[i];
    if (unit->type == enum_Charset) {
      // select part
      struct CharsetPart *part0 = &charset->parts[ unit->inv];
      struct CharsetPart *part1 = &charset->parts[!unit->inv];
      // copy without duplicate
      Charset *target = unit->target;
      Set_update(part0->plains, target->parts[CT_NORMAL].plains);
      Set_update(part0->ranges, target->parts[CT_NORMAL].ranges);
      Set_update(part1->plains, target->parts[CT_INVERSE].plains);
      Set_update(part1->ranges, target->parts[CT_INVERSE].ranges);
    } else if (unit->type == enum_CHAR) {
      // select part
      struct CharsetPart *tap = &charset->parts[unit->inv];
      // update plains
      char_t the_char = (char_t) (uint64_t) unit->target;
      Set_add(tap->plains, (void *) (uint64_t) the_char);
    } else if (unit->type == enum_Range) {
      // select part
      struct CharsetPart *tap = &charset->parts[unit->inv];
      // update range
      Range_set_update(tap->ranges, unit->target);
    } else {
      // never be touched
    }
  }
  releaseUnitArray(_arg1, allocator);
  Array_destroy(_arg1);
  return charset;
}

Charset *p_Charset_1(Token argv[], RegexContext *, const Allocator * const allocator) {
  uint32_t _arg1 = (uint32_t) (uint64_t) argv[0].value;

  Charset *charset = allocator->calloc(1, sizeof(Charset));
  // create parts
  charset->parts[CT_NORMAL].plains  = Set_new(enum_CHAR,  nullptr, allocator);
  charset->parts[CT_NORMAL].ranges  = Set_new(enum_Range, nullptr, allocator);
  charset->parts[CT_INVERSE].plains = Set_new(enum_CHAR,  nullptr, allocator);
  charset->parts[CT_INVERSE].ranges = Set_new(enum_Range, nullptr, allocator);

  auto normal_part = ESCAPE_CHARSETS[_arg1].parts[CT_NORMAL];
  auto inverse_part = ESCAPE_CHARSETS[_arg1].parts[CT_INVERSE];
  for (uint32_t i = 0; i < normal_part.n_plains; i++) {
    Set_add(charset->parts[CT_NORMAL].plains, (void *) (uint64_t) normal_part.plains[i]);
  }
  for (uint32_t i = 0; i < normal_part.n_ranges; i++) {
    Range_set_update(charset->parts[CT_NORMAL].ranges,  &normal_part.ranges[i]);
  }
  for (uint32_t i = 0; i < inverse_part.n_plains; i++) {
    Set_add(charset->parts[CT_NORMAL].plains, (void *) (uint64_t) inverse_part.plains[i]);
  }
  for (uint32_t i = 0; i < inverse_part.n_ranges; i++) {
    Range_set_update(charset->parts[CT_NORMAL].ranges,  &inverse_part.ranges[i]);
  }

  return charset;
}

Unit *p_Unit_0(Token argv[], RegexContext *, const Allocator * const allocator) {
  Terminal *_arg0 = argv[0].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_CHAR;
  unit->inv = false;
  unit->target = (void *) (uint64_t) _arg0->value;
  return unit;
}

Unit *p_Unit_1(Token argv[], RegexContext *, const Allocator * const allocator) {
  Range *_arg0 = argv[0].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Range;
  unit->inv = false;
  unit->target = (void *) _arg0;
  return unit;
}

Unit *p_Unit_2(Token argv[], RegexContext *, const Allocator * const allocator) {
  Range *_arg0 = argv[0].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Charset;
  unit->inv = false;
  unit->target = (void *) _arg0;
  return unit;
}

Unit *p_Unit_3(Token argv[], RegexContext *, const Allocator * const allocator) {
  Terminal *_arg1 = argv[1].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_CHAR;
  unit->inv = true;
  unit->target = (void *) (uint64_t) _arg1->value;
  return unit;
}

Unit *p_Unit_4(Token argv[], RegexContext *, const Allocator * const allocator) {
  Range *_arg1 = argv[1].value;
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Charset;
  unit->inv = true;
  unit->target = (void *) _arg1;
  return unit;
}

UnitArray *p_UnitArray_0(Token argv[], RegexContext *, const Allocator * const allocator) {
  UnitArray *_arg0 = argv[0].value;
  Unit *_arg1 = argv[1].value;
  Array_append(_arg0, _arg1, 1);
  allocator->free(_arg1);
  return _arg0;
}

UnitArray *p_UnitArray_1(Token argv[], RegexContext *, const Allocator * const allocator) {
  Unit *_arg0 = argv[0].value;
  UnitArray *array = Array_new(sizeof(Unit), enum_Unit, allocator);
  Array_append(array, _arg0, 1);
  allocator->free(_arg0);
  return array;
}

Group *p_Group_0(Token argv[], RegexContext *, const Allocator *allocator) {
  Regexp *_arg1 = argv[1].value;
  Group *group = allocator->calloc(1, sizeof(Group));
  group->regexp = _arg1;
  return group;
}

Object *p_Object_0(Token argv[], RegexContext *, const Allocator * const allocator) {
  void *_arg0 = argv[0].value;
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_CHAR;
  obj->inv = false;
  obj->target = _arg0;
  return obj;
}

Object *p_Object_1(Token argv[], RegexContext *, const Allocator * const allocator) {
  Charset *_arg0 = argv[0].value;
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Charset;
  obj->inv = false;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_2(Token argv[], RegexContext *, const Allocator * const allocator) {
  Group *_arg0 = argv[0].value;
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Group;
  obj->inv = false;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_3(Token argv[], RegexContext *, const Allocator * const allocator) {
  Quantified *_arg0 = argv[0].value;
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Quantified;
  obj->inv = false;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_4(Token argv[], RegexContext *, const Allocator * const allocator) {
  void *_arg0 = argv[1].value;
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_CHAR;
  obj->inv = true;
  obj->target = _arg0;
  return obj;
}

Object *p_Object_5(Token argv[], RegexContext *, const Allocator * const allocator) {
  Charset *_arg1 = argv[1].value;
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Charset;
  obj->inv = true;
  obj->target = _arg1;
  return obj;
}

Object *p_Object_6(Token argv[], RegexContext *, const Allocator * const allocator) {
  Group *_arg1 = argv[1].value;
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Group;
  obj->inv = true;
  obj->target = _arg1;
  return obj;
}

Object *p_Object_7(Token argv[], RegexContext *, const Allocator * const) {
  Object *_arg1 = argv[1].value;
  _arg1->ass = true;
  return _arg1;
}

Quantified *p_Quantified_0(Token argv[], RegexContext *, const Allocator * const allocator) {
  Object *_arg0 = argv[0].value;
  Quantifier *_arg1 = argv[1].value;
  Quantified *quantified = allocator->calloc(1, sizeof(Quantified));
  memcpy(&quantified->quant, _arg1, sizeof(Quantifier));
  memcpy(&quantified->object, _arg0, sizeof(Object));
  allocator->free(_arg0);
  allocator->free(_arg1);
  return quantified;
}

Quantifier *p_Quantifier_0(Token [], RegexContext *, const Allocator * const allocator) {
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 0;
  quant->max = 1;
  return quant;
}

Quantifier *p_Quantifier_1(Token [], RegexContext *, const Allocator * const allocator) {
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 1;
  quant->max = 0;
  return quant;
}

Quantifier *p_Quantifier_2(Token [], RegexContext *, const Allocator * const allocator) {
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 0;
  quant->max = 0;
  return quant;
}

Quantifier *p_Quantifier_3(Token argv[], RegexContext *, const Allocator * const allocator) {
  uint64_t _arg1 = (uint64_t) argv[1].value;
  uint64_t _arg3 = (uint64_t) argv[3].value;
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = _arg1;
  quant->max = _arg3;
  return quant;
}

Quantifier *p_Quantifier_4(Token argv[], RegexContext *, const Allocator * const allocator) {
  uint64_t _arg1 = (uint64_t) argv[1].value;
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = _arg1;
  quant->max = 0ULL;
  return quant;
}

Quantifier *p_Quantifier_5(Token argv[], RegexContext *, const Allocator * const allocator) {
  uint64_t _arg2 = (uint64_t) argv[2].value;
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 0ULL;
  quant->max = _arg2;
  return quant;
}

Quantifier *p_Quantifier_6(Token argv[], RegexContext *, const Allocator * const allocator) {
  uint64_t _arg1 = (uint64_t) argv[1].value;
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = _arg1;
  quant->max = _arg1;
  return quant;
}

Range *p_Range_0(Token argv[], RegexContext *, const Allocator * const allocator) {
  char_t _arg0 = (uint64_t) argv[0].value;
  char_t _arg2 = (uint64_t) argv[2].value;
  Range *rng = allocator->calloc(1, sizeof(Range));
  rng->min = _arg0;
  rng->max = _arg2;
  return rng;
}

Regexp *p_Regexp_0(Token argv[], RegexContext *, const Allocator * const allocator) {
  Regexp *_arg0 = argv[0].value;
  Branch *_arg2 = argv[2].value;
  Array_append(_arg0, _arg2, 1);
  allocator->free(_arg2);
  return _arg0;
}

Regexp *p_Regexp_1(Token argv[], RegexContext *, const Allocator * const allocator) {
  Branch *_arg0 = argv[0].value;
  Regexp *regex = Array_new(sizeof_array, enum_Branch, allocator);
  Array_append(regex, _arg0, 1);
  allocator->free(_arg0);
  return regex;
}

Regexp *p_Regexp_2(Token [], RegexContext *, const Allocator * const) {
  return (Regexp *) enum_Regexp;
}

Regexp *p__Regexp__(Token argv[], RegexContext *, const Allocator *) {
  return (Regexp *) argv[0].value;
}

Regexp *failed_to_get_next_state(Stack *state_stack, Stack *token_stack, void *result,
                                 uint32_t result_type, const Allocator *allocator);
Regexp *failed_to_produce(Stack *state_stack, Stack *token_stack, Token *, uint32_t,
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

Regexp *failed_to_produce(Stack *state_stack, Stack *token_stack, Token *, uint32_t,
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
