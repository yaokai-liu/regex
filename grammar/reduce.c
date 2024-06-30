/**
 * Project Name: regex
 * Module Name: grammar
 * Filename: reduce.c
 * Creator: Yaokai Liu
 * Create Date: 24-6-29
 * Copyright (c) 2024 Yaokai Liu. All rights reserved.
 **/

#include "reduce.gen.h"
#include "terminal.h"
#include "tokens.gen.h"
#include <string.h>

#define ALLOC_LEN 32

thread_local static uint32_t STATE_COUNT = 0;

struct Branch *p_Branch_0(void *argv[], const Allocator *allocator) {
  struct Object *_arg0 = argv[0];
  struct Branch *_arg1 = argv[1];
  if (_arg1->length + 1 >= _arg1->alloc) {
    _arg1->alloc += ALLOC_LEN;
    size_t size = _arg1->alloc * sizeof(struct Object);
    void *p = allocator->realloc(_arg1->objects, size);
    if (!p) { return nullptr; }
    _arg1->objects = p;
  }
  struct Object *dest = &_arg1->objects[_arg1->length];
  memcpy(dest, _arg0, sizeof(struct Object));
  _arg1->length++;
  return _arg1;
}

struct Branch *p_Branch_1(void *argv[], const Allocator *allocator) {
  struct Object *_arg0 = argv[0];
  struct Branch *br = allocator->calloc(1, sizeof(struct Branch));
  br->objects = allocator->malloc(ALLOC_LEN * sizeof(struct Object));
  br->alloc = ALLOC_LEN;
  memcpy(br->objects, _arg0, sizeof(struct Object));
  br->length = 1;
  br->post_state = STATE_COUNT++;
  return br;
}

struct Charset *p_Charset_0(void *argv[], const Allocator *) {
  //    Terminal *_arg0 = argv[0];
  struct UnitArray *_arg1 = argv[1];
  //    Terminal *_arg2 = argv[2];
  return (struct Charset *) _arg1;
}

struct Unit *p_Unit_0(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  struct Unit *unit = allocator->calloc(1, sizeof(struct Unit));
  unit->type = CHAR;
  unit->inv = false;
  unit->target = (void *) (uint64_t) _arg0->value;
  return unit;
}

struct Unit *p_Unit_1(void *argv[], const Allocator *allocator) {
  struct Range *_arg0 = argv[0];
  struct Unit *unit = allocator->calloc(1, sizeof(struct Unit));
  unit->type = Range;
  unit->inv = false;
  unit->target = (void *) _arg0;
  return unit;
}

struct Unit *p_Unit_2(void *argv[], const Allocator *allocator) {
  struct Range *_arg0 = argv[0];
  struct Unit *unit = allocator->calloc(1, sizeof(struct Unit));
  unit->type = Charset;
  unit->inv = false;
  unit->target = (void *) _arg0;
  return unit;
}

struct Unit *p_Unit_3(void *argv[], const Allocator *allocator) {
  struct Unit *unit = p_Unit_0(argv, allocator);
  unit->inv = true;
  return unit;
}

struct Unit *p_Unit_4(void *argv[], const Allocator *allocator) {
  struct Unit *unit = p_Unit_1(argv, allocator);
  unit->inv = true;
  return unit;
}

struct Unit *p_Unit_5(void *argv[], const Allocator *allocator) {
  struct Unit *unit = p_Unit_2(argv, allocator);
  unit->inv = true;
  return unit;
}

struct UnitArray *p_UnitArray_0(void *argv[], const Allocator *allocator) {
  struct Unit *_arg0 = argv[0];
  struct UnitArray *_arg1 = argv[1];
  if (_arg1->length + 1 >= _arg1->alloc) {
    _arg1->alloc += ALLOC_LEN;
    size_t size = _arg1->alloc * sizeof(struct Unit);
    void *p = allocator->realloc(_arg1->array, size);
    if (!p) { return nullptr; }
    _arg1->array = p;
  }
  struct Unit *dest = &_arg1->array[_arg1->length];
  memcpy(dest, _arg0, sizeof(struct Unit));
  _arg1->length++;
  return _arg1;
}

struct UnitArray *p_UnitArray_1(void *argv[], const Allocator *allocator) {
  struct Unit *_arg0 = argv[0];
  struct UnitArray *array = allocator->calloc(1, sizeof(struct UnitArray));
  array->array = allocator->malloc(ALLOC_LEN * sizeof(struct Unit));
  array->alloc = ALLOC_LEN;
  memcpy(array->array, _arg0, sizeof(struct Unit));
  array->length = 1;
  return array;
}

struct Group *p_Group_0(void *argv[], const Allocator *) {
  struct Regexp *_arg0 = argv[0];
  return (struct Group *) _arg0;
}

struct NumQuantifier *p_NumQuantifier_0(void *argv[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  //    Terminal *_arg2 = argv[2];
  Terminal *_arg3 = argv[3];
  //    Terminal *_arg4 = argv[4];
  struct NumQuantifier *quant = allocator->calloc(1, sizeof(struct NumQuantifier));
  quant->min = _arg1->value;
  quant->max = _arg3->value;
  return quant;
}

struct NumQuantifier *p_NumQuantifier_1(void *argv[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  Terminal *_arg1 = argv[1];
  //    Terminal *_arg2 = argv[2];
  struct NumQuantifier *quant = allocator->calloc(1, sizeof(struct NumQuantifier));
  quant->min = _arg1->value;
  quant->max = _arg1->value;
  return quant;
}

struct Object *p_Object_0(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  struct Object *obj = allocator->calloc(1, sizeof(struct Object));
  obj->type = _arg0->type;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) (uint64_t) _arg0->value;
  return obj;
}

struct Object *p_Object_1(void *argv[], const Allocator *allocator) {
  struct Charset *_arg0 = argv[0];
  struct Object *obj = allocator->calloc(1, sizeof(struct Object));
  obj->type = Charset;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

struct Object *p_Object_2(void *argv[], const Allocator *allocator) {
  struct Group *_arg0 = argv[0];
  struct Object *obj = allocator->calloc(1, sizeof(struct Object));
  obj->type = Group;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

struct Object *p_Object_3(void *argv[], const Allocator *allocator) {
  struct Quantified *_arg0 = argv[0];
  struct Object *obj = allocator->calloc(1, sizeof(struct Object));
  obj->type = Quantified;
  obj->inv = false;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

struct Object *p_Object_4(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  struct Object *obj = allocator->calloc(1, sizeof(struct Object));
  obj->type = _arg0->type;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) (uint64_t) _arg0->value;
  return obj;
}

struct Object *p_Object_5(void *argv[], const Allocator *allocator) {
  struct Charset *_arg0 = argv[0];
  struct Object *obj = allocator->calloc(1, sizeof(struct Object));
  obj->type = Charset;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) _arg0;
  return obj;
}

struct Object *p_Object_6(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  struct Object *obj = allocator->calloc(1, sizeof(struct Object));
  obj->type = _arg0->type;
  obj->inv = true;
  obj->post_state = STATE_COUNT++;
  obj->target = (void *) (uint64_t) _arg0->value;
  return obj;
}

struct Quantified *p_Quantified_0(void *argv[], const Allocator *allocator) {
  struct Object *_arg0 = argv[0];
  struct Quantifier *_arg1 = argv[1];
  struct Quantified *quant = allocator->calloc(1, sizeof(struct Quantified));
  memcpy(&quant->quant, _arg1, sizeof(struct Quantifier));
  memcpy(&quant->object, _arg0, sizeof(struct Object));
  allocator->free(_arg0);
  allocator->free(_arg1);
  return quant;
}

struct Quantifier *p_Quantifier_0(void *[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  struct Quantifier *quant = allocator->calloc(1, sizeof(struct Quantifier));
  quant->min = 0;
  quant->max = 1;
  return quant;
}

struct Quantifier *p_Quantifier_1(void *[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  struct Quantifier *quant = allocator->calloc(1, sizeof(struct Quantifier));
  quant->min = 1;
  quant->max = 0;
  return quant;
}

struct Quantifier *p_Quantifier_2(void *[], const Allocator *allocator) {
  //    Terminal *_arg0 = argv[0];
  struct Quantifier *quant = allocator->calloc(1, sizeof(struct Quantifier));
  quant->min = 0;
  quant->max = 0;
  return quant;
}

struct Quantifier *p_Quantifier_3(void *argv[], const Allocator *) {
  struct NumQuantifier *_arg0 = argv[0];
  return (struct Quantifier *) _arg0;
}

struct Range *p_Range_0(void *argv[], const Allocator *allocator) {
  Terminal *_arg0 = argv[0];
  //    Terminal *_arg1 = argv[1];
  Terminal *_arg2 = argv[2];
  struct Range *rng = allocator->calloc(1, sizeof(struct Range));
  rng->min = _arg0->value;
  rng->max = _arg2->value;
  return rng;
}

struct Regexp *p_Regexp_0(void *argv[], const Allocator *allocator) {
  struct Branch *_arg0 = argv[0];
  //    Terminal *_arg1 = argv[1];
  struct Regexp *_arg2 = argv[2];
  if (_arg2->length + 1 >= _arg2->alloc) {
    _arg2->alloc += ALLOC_LEN;
    size_t size = _arg2->alloc * sizeof(struct Branch);
    void *p = allocator->realloc(_arg2->branches, size);
    if (!p) { return nullptr; }
    _arg2->branches = p;
  }
  struct Branch *dest = &_arg2->branches[_arg2->length];
  memcpy(dest, _arg0, sizeof(struct Branch));
  _arg2->length++;
  return _arg2;
}

struct Regexp *p_Regexp_1(void *argv[], const Allocator *allocator) {
  struct Branch *_arg0 = argv[0];
  struct Regexp *regex = allocator->calloc(1, sizeof(struct Regexp));
  regex->branches = allocator->malloc(ALLOC_LEN * sizeof(struct Branch));
  regex->alloc = ALLOC_LEN;
  memcpy(regex->branches, _arg0, sizeof(struct Branch));
  regex->length = 1;
  return regex;
}

struct Regexp *p___EXTEND_RULE__(void *argv[], const Allocator *) {
  struct Regexp *regex = argv[0];
  return regex;
}

