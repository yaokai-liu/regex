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
#include "target.h"
#include "terminal.h"
#include "tokens.gen.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_LEN 32

thread_local static uint32_t STATE_COUNT = 0;

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
  charset->taps[CT_NORMAL].plains = Array_new(sizeof(char_t), allocator);
  charset->taps[CT_NORMAL].ranges = Array_new(sizeof(Range), allocator);
  charset->taps[CT_INVERSE].plains = Array_new(sizeof(char_t), allocator);
  charset->taps[CT_INVERSE].ranges = Array_new(sizeof(Range), allocator);

  uint32_t length = Array_length(_arg1);
  for (uint32_t i = 0; i < length; i++) {
    Unit *unit = Array_get(_arg1, i);
    if (unit->type == enum_Charset) {
      struct charset_tap *tap0 = &charset->taps[unit->inv];
      struct charset_tap *tap1 = &charset->taps[!unit->inv];
      Charset *target = unit->target;
      Array_no_duplicated_concat(tap0->plains, target->taps[CT_NORMAL].plains);
      Array_no_duplicated_concat(tap0->ranges, target->taps[CT_NORMAL].ranges);
      Array_no_duplicated_concat(tap1->plains, target->taps[CT_INVERSE].plains);
      Array_no_duplicated_concat(tap1->ranges, target->taps[CT_INVERSE].ranges);
      releaseCharset(unit->target, allocator);
      allocator->free(unit->target);
    } else if (unit->type == enum_CHAR) {
      struct charset_tap *tap = &charset->taps[unit->inv];
      char_t the_char = (char_t) (uint64_t) unit->target;
      Array_append(tap->plains, &the_char, 1);
    } else if (unit->type == enum_Range) {
      struct charset_tap *tap = &charset->taps[unit->inv];
      Array_append(tap->ranges, unit->target, 1);
      allocator->free(unit->target);
    } else {
      // never be touched
    }
  }
  Array_reset(_arg1, nullptr);
  allocator->free(_arg1);
  return charset;
}

Sequence *p_Sequence_0(void *argv[], const Allocator * const allocator) {
  Terminal *_arg0 = argv[0];
  Sequence *seq = Array_new(sizeof(char_t), allocator);
  Array_append(seq, &_arg0->value, 1);
  return seq;
}

Sequence *p_Sequence_1(void *argv[], const Allocator * const allocator) {
  Sequence *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  if (allocator) { argv[MAX_ARGC - 1] = "'-Wall' requires it be used, make the compiler happy."; }
  Array_append(_arg0, &_arg1->value, 1);
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
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_1(void *argv[], const Allocator * const allocator) {
  Charset *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Charset;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_2(void *argv[], const Allocator * const allocator) {
  Group *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Group;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_3(void *argv[], const Allocator * const allocator) {
  Quantified *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Quantified;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_4(void *argv[], const Allocator * const allocator) {
  //  Terminal *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = _arg1->type;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) (uint64_t) _arg1->value;
  return obj;
}

Object *p_Object_5(void *argv[], const Allocator * const allocator) {
  //  Charset *_arg0 = argv[0];
  Charset *_arg1 = argv[1];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Charset;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = _arg1;
  return obj;
}

Object *p_Object_6(void *argv[], const Allocator * const allocator) {
  //  Terminal *_arg0 = argv[0];
  Group *_arg1 = argv[1];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Group;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = _arg1;
  return obj;
}

Quantified *p_Quantified_0(void *argv[], const Allocator * const allocator) {
  Object *_arg0 = argv[0];
  Quantifier *_arg1 = argv[1];
  Quantified *quant = allocator->calloc(1, sizeof(Quantified));
  memcpy(&quant->quant, _arg1, sizeof(Quantifier));
  memcpy(&quant->object, _arg0, sizeof(Object));
  allocator->free(_arg0);
  allocator->free(_arg1);
  return quant;
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
