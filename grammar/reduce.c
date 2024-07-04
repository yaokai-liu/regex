/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: reduce.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "array.h"
#include "reduce.gen.h"
#include "terminal.h"
#include "tokens.gen.h"
#include <string.h>

#define ALLOC_LEN 32

thread_local static uint32_t STATE_COUNT = 0;

Branch *p_Branch_0(void *argv[], const Allocator *allocator) {
  Object *_arg0 = argv[0];
  Branch *_arg1 = argv[1];
  if (_arg1->length + 1 >= _arg1->alloc) {
    _arg1->alloc += ALLOC_LEN;
    size_t size = _arg1->alloc * sizeof(Object);
    void *p = allocator->realloc(_arg1->objects, size);
    if (!p) { return nullptr; }
    _arg1->objects = p;
  }
  Object *dest = &_arg1->objects[_arg1->length];
  memcpy(dest, _arg0, sizeof(Object));
  allocator->free(_arg0);
  _arg1->length++;
  return _arg1;
}

Branch *p_Branch_1(void *argv[], const Allocator *allocator) {
  Object *_arg0 = argv[0];
  Branch *br = allocator->calloc(1, sizeof(Branch));
  br->objects = allocator->malloc(ALLOC_LEN * sizeof(Object));
  br->alloc = ALLOC_LEN;
  memcpy(br->objects, _arg0, sizeof(Object));
  allocator->free(_arg0);
  br->length = 1;
  br->post_state = STATE_COUNT++;
  return br;
}

Charset *p_Charset_0(void *argv[], const Allocator *) {
  //    Terminal *_arg0 = argv[0];
  UnitArray *_arg1 = argv[1];
  //    Terminal *_arg2 = argv[2];
  return (Charset *) _arg1;
}

Sequence *p_Sequence_0(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  Sequence *seq = allocator->calloc(1, sizeof(Sequence));
  seq->plains = allocator->malloc(ALLOC_LEN * sizeof(uint8_t));
  seq->alloc = ALLOC_LEN;
  seq->plains[0] = _arg0->value;
  seq->length = 1;
  return seq;
}

Sequence *p_Sequence_1(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  Sequence *_arg1 = argv[1];
  if (_arg1->length + 1 >= _arg1->alloc) {
    _arg1->alloc += ALLOC_LEN;
    size_t size = _arg1->alloc * sizeof(uint8_t);
    void *p = allocator->realloc(_arg1->plains, size);
    if (!p) { return nullptr; }
    _arg1->plains = p;
  }
  _arg1->plains[_arg1->length] = _arg0->value;
  _arg1->length++;
  return _arg1;
}

Unit *p_Unit_0(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_CHAR;
  unit->inv = false;
  unit->target = (void *) (uint64_t) _arg0->value;
  return unit;
}

Unit *p_Unit_1(void *argv[], const Allocator *allocator) {
  Range *_arg0 = argv[0];
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Range;
  unit->inv = false;
  unit->target = (void *) _arg0;
  return unit;
}

Unit *p_Unit_2(void *argv[], const Allocator *allocator) {
  Range *_arg0 = argv[0];
  Unit *unit = allocator->calloc(1, sizeof(Unit));
  unit->type = enum_Charset;
  unit->inv = false;
  unit->target = (void *) _arg0;
  return unit;
}

Unit *p_Unit_3(void *argv[], const Allocator *allocator) {
  Unit *unit = p_Unit_0(argv, allocator);
  unit->inv = true;
  return unit;
}

Unit *p_Unit_4(void *argv[], const Allocator *allocator) {
  Unit *unit = p_Unit_1(argv, allocator);
  unit->inv = true;
  return unit;
}

Unit *p_Unit_5(void *argv[], const Allocator *allocator) {
  Unit *unit = p_Unit_2(argv, allocator);
  unit->inv = true;
  return unit;
}

UnitArray *p_UnitArray_0(void *argv[], const Allocator *allocator) {
  Unit *_arg0 = argv[0];
  UnitArray *_arg1 = argv[1];
  Array_append(_arg1, _arg0, 1);
  allocator->free(_arg0);
  return _arg1;
}

UnitArray *p_UnitArray_1(void *argv[], const Allocator *allocator) {
  Unit *_arg0 = argv[0];
  UnitArray *array = Array_new(sizeof(Unit), allocator);
  Array_append(array, _arg0, 1);
  allocator->free(_arg0);
  return array;
}

Group *p_Group_0(void *argv[], const Allocator *) {
  //  Terminal *_arg0 = argv[0];
  Regexp *_arg1 = argv[1];
  //  Terminal *_arg2 = argv[2];
  return (Group *) _arg1;
}

Object *p_Object_0(void *argv[], const Allocator *allocator) {
  Sequence *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Sequence;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_1(void *argv[], const Allocator *allocator) {
  Charset *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Charset;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_2(void *argv[], const Allocator *allocator) {
  Group *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Group;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_3(void *argv[], const Allocator *allocator) {
  Quantified *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Quantified;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_4(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = _arg0->type;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) (uint64_t) _arg0->value;
  return obj;
}

Object *p_Object_5(void *argv[], const Allocator *allocator) {
  Charset *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = enum_Charset;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

Object *p_Object_6(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  Object *obj = allocator->calloc(1, sizeof(Object));
  obj->type = _arg0->type;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) (uint64_t) _arg0->value;
  return obj;
}

Quantified *p_Quantified_0(void *argv[], const Allocator *allocator) {
  Object *_arg0 = argv[0];
  Quantifier *_arg1 = argv[1];
  Quantified *quant = allocator->calloc(1, sizeof(Quantified));
  memcpy(&quant->quant, _arg1, sizeof(Quantifier));
  memcpy(&quant->object, _arg0, sizeof(Object));
  allocator->free(_arg0);
  allocator->free(_arg1);
  return quant;
}

Quantifier *p_Quantifier_0(void *[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 0;
  quant->max = 1;
  return quant;
}

Quantifier *p_Quantifier_1(void *[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 1;
  quant->max = 0;
  return quant;
}

Quantifier *p_Quantifier_2(void *[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = 0;
  quant->max = 0;
  return quant;
}

Quantifier *p_Quantifier_3(void *argv[], const Allocator *allocator) {
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

Quantifier *p_Quantifier_4(void *argv[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  //    Terminal *_arg2 = argv[2];
  Quantifier *quant = allocator->calloc(1, sizeof(Quantifier));
  quant->min = _arg1->value;
  quant->max = _arg1->value;
  return quant;
}

Range *p_Range_0(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  //    Terminal *_arg1 = argv[1];
  Terminal *_arg2 = argv[2];
  Range *rng = allocator->calloc(1, sizeof(Range));
  rng->min = _arg0->value;
  rng->max = _arg2->value;
  return rng;
}

Regexp *p_Regexp_0(void *argv[], const Allocator *allocator) {
  Branch *_arg0 = argv[0];
  //    Terminal *_arg1 = argv[1];
  Regexp *_arg2 = argv[2];
  if (_arg2->length + 1 >= _arg2->alloc) {
    _arg2->alloc += ALLOC_LEN;
    size_t size = _arg2->alloc * sizeof(Branch);
    void *p = allocator->realloc(_arg2->branches, size);
    if (!p) { return nullptr; }
    _arg2->branches = p;
  }
  Branch *dest = &_arg2->branches[_arg2->length];
  memcpy(dest, _arg0, sizeof(Branch));
  allocator->free(_arg0);
  _arg2->length++;
  return _arg2;
}

Regexp *p_Regexp_1(void *argv[], const Allocator *allocator) {
  Branch *_arg0 = argv[0];
  Regexp *regex = allocator->calloc(1, sizeof(Regexp));
  regex->branches = allocator->malloc(ALLOC_LEN * sizeof(Branch));
  regex->alloc = ALLOC_LEN;
  memcpy(regex->branches, _arg0, sizeof(Branch));
  allocator->free(_arg0);
  regex->length = 1;
  return regex;
}

Regexp *p___EXTEND_RULE__(void *argv[], const Allocator *) {
  Regexp *regex = argv[0];
  return regex;
}
